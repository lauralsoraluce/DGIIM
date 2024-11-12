//**********************************************************************
// BY LAURA LÁZARO SORALUCE
//**********************************************************************

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales
const unsigned num_jugadores = 3; // Un número n entre 2 y 4.
const unsigned max_rellenos = aleatorio<1,5>(); // Número de veces que el cocinero rellena el plato de galletas
int galletas[num_jugadores]={0,0,0}; // Número de galletas que ha cogido cada jugador durante la partida
bool bloqueados[num_jugadores] = {false,false,false};
int n_bloqueados=0;
bool esperando[num_jugadores]={false,false,false}; // Dice si las hebras bloqueadas están pendientes de que se les haga wait

//**********************************************************************
// Monitor

class Juego : public HoareMonitor
{
 private:
 int plato[num_jugadores][num_jugadores];

 CondVar             // colas condicion:
	coger_galleta[num_jugadores];

 public:                    // constructor y métodos públicos
   Juego() ;             // constructor
   bool Coger(int x, int fila, int columna);                
   void Cocinar();
   void Liberar();
   void Esperar(int x);
   void MostrarPlato();
   bool ComprobarVacio();
} ;

Juego::Juego() 
{

	for (int i=0;i<num_jugadores; i++){
		coger_galleta[i] = newCondVar();
		for (int j=0; j<num_jugadores; j++) {
			plato[i][j]=aleatorio<0,4>(); //Rellenamos el plato la primera vez, con un número aleatorio, entre 0 y 4, de galletas en cada casilla
		}
	}
}

bool Juego::ComprobarVacio()
{
	bool vacio = true;
	for (int i=0; i<num_jugadores; i++) {
		for (int j=0; j<num_jugadores; j++){
			if (plato[i][j]>0)
				vacio=false;
		}
	}
	return vacio;
}

bool Juego::Coger (int jugador, int fila, int columna) 
{
		
	if (plato[fila][columna]>0){
		
		plato[fila][columna]--;
		//campo[ant_x][ant_y]=-1;
		return true;
	}
	else {
		return false; // Si la posición de la que intenta coger el jugador está vacía, se tiene que bloquear, por lo que devuelve que no se ha podido coger ninguna galleta
	}
}

void Juego::Cocinar () 
{
	
	// Si se recorre una fila entera
	/*for (int i=0; i<num_jugadores; i++) {
		if (campo[num][i]>-1){
			cout << "JUGADOR ENCONTRADO: " << campo[num][i] << endl;
			int jugador_encontrado=campo[num][i];
			vidas[jugador_encontrado]--;
			bloqueados[jugador_encontrado]=true;
			esperando[jugador_encontrado]=true;
			n_bloqueados++;
			campo[num][i]=-1;
			
		}
	}*/
	
	
	for (int i=0; i<num_jugadores; i++) {
		for (int j=0; j<num_jugadores; j++) {
			plato[i][j]= plato[i][j]+aleatorio<0,4>(); 
			//En cada casilla añade un número aleatorio de galletas, entre 0 y 4
			
			
		}
	}
}

void Juego::Esperar(int i) 
{
	coger_galleta[i].wait();
}

void Juego::Liberar()
{
	for (int i=0; i<num_jugadores; i++){
		coger_galleta[i].signal();
	}
}

void Juego::MostrarPlato()
{
	for(int i = 0; i < num_jugadores; i++){
    	cout << endl;
		for(int j = 0; j < num_jugadores; j++){
			cout << "[\t" << plato[i][j] << "\t]";
		}
  	}

  	cout << endl << endl;
}

void hebra_cocinero (MRef<Juego> Mario) 
{
	int veces = 0;
	while (veces<max_rellenos){
		this_thread::sleep_for( chrono::milliseconds( aleatorio<100,180>() ));
		//int num=aleatorio<0,num_jugadores-1>();
		cout << "Cocinero reponiendo galletas..." << endl;
		Mario->Cocinar();
		veces++;
	}
	//exit(0);
}

void hebra_jugador(MRef<Juego> Mario, int i) 
{
	/*cout << "PLATO ORIGINAL: " << endl;
	Mario->MostrarPlato();
	cout << endl << endl;*/
	
	while (!Mario->ComprobarVacio()) 
	{
		this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>()));
		
		if (!bloqueados[i]){
			int columna = aleatorio<0,num_jugadores-1>();
			int fila = aleatorio<0,num_jugadores-1>();
			
			bool cogido = Mario->Coger(i, fila, columna);
			if (cogido) {
				Mario->MostrarPlato();
				galletas[i]++;
				
				cout << "J" << i << ": cogí una galleta de [" << fila << ", " << columna << "]" << endl;
				
				cout << "Galletas: ";
				for (int i=0; i<num_jugadores; i++) {
					cout << galletas[i] << " ";
				}
				cout << endl;
			}
			else {
				bloqueados[i]=true;
				n_bloqueados++;
				esperando[i]=true;
				cout << "J" << i << ": intenté coger de [" << fila << ", " << columna << "] y me voy a bloquear (hay " << n_bloqueados << " hebras bloqueadas) " << endl;
			}
		}
		else {
			if (n_bloqueados==num_jugadores){
				n_bloqueados = 0;
				Mario->Liberar(); //coger_galleta.signal();
				esperando[i]=false;
				
				for (int i=0; i<num_jugadores; i++) {
					bloqueados[i]=false;
				}
			}
			else {
				if (esperando[i]) {
					Mario->Esperar(i); //coger_galleta[i].wait();
					esperando[i]=false;
				}
			}
		}
		
	}
	
	exit(0);
}

//**********************************************************************
// MAIN - PROGRAMA PRINCIPAL

int main() {

	MRef<Juego> Mario = Create<Juego>() ;
	
	thread hebras_jugadores[num_jugadores];
	
	for (int i=0; i<num_jugadores; i++) {
		hebras_jugadores[i] = thread (hebra_jugador, Mario, i);
	}
	
	thread cocinero(hebra_cocinero, Mario);

	for (int i=0; i<num_jugadores; i++) {
		hebras_jugadores[i].join();
	}
	cocinero.join();
	
	return 0;

}








