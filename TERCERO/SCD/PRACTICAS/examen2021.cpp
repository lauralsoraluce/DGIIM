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

const unsigned num_jugadores =3;
int vidas[num_jugadores]={3,3,3};
bool bloqueados[num_jugadores]={false, false, false};
bool esperando[num_jugadores]={false, false, false};
int n_bloqueados=0;


//**********************************************************************
// Monitor

class Juego : public HoareMonitor
{
 private:
 int campo[num_jugadores][num_jugadores];

 CondVar             // colas condicion:
	moverse[num_jugadores];

 public:                    // constructor y métodos públicos
   Juego() ;             // constructor
   bool Moverme(int x, int fila, int columna, int ant_x, int ant_y);                
   void EnemigoMover(int num);
   void Liberar();
   void Esperar(int x);
   void MostrarCampo();
} ;

Juego::Juego() 
{

	for (int i=0;i<num_jugadores; i++){
		moverse[i] = newCondVar();
		for (int j=0; j<num_jugadores; j++) {
			campo[i][j]=-1;
		}
	}
}

bool Juego::Moverme (int jugador, int fila, int columna, int ant_x, int ant_y) 
{
		
	if (campo[fila][columna]==-1){
		
		campo[fila][columna]=jugador;
		campo[ant_x][ant_y]=-1;
		return true;
	}
	else {
		return false;
	}
}

void Juego::EnemigoMover (int num) 
{
	
	// Si se recorre una fila entera
	for (int i=0; i<num_jugadores; i++) {
		if (campo[num][i]>-1){
			cout << "JUGADOR ENCONTRADO: " << campo[num][i] << endl;
			int jugador_encontrado=campo[num][i];
			vidas[jugador_encontrado]--;
			bloqueados[jugador_encontrado]=true;
			esperando[jugador_encontrado]=true;
			n_bloqueados++;
			campo[num][i]=-1;
			
		}
	}
}

void Juego::MostrarCampo(){
	/*cout << endl << "|\t" << campo[0][0] << "|\t" << campo[0][1] << "|\t" << campo[0][2] << "|\t" << endl;
	cout << "|\t" << campo[1][0] << "|\t" << campo[1][1] << "|\t" << campo[1][2] << "|\t" << endl;
	cout << "|\t" << campo[2][0] << "|\t" << campo[2][1] << "|\t" << campo[2][2] << "|\t" << endl<< endl;*/
	for(int i = 0; i < num_jugadores; i++){
    	cout << endl;
		for(int j = 0; j < num_jugadores; j++){
			cout << "[\t" << campo[i][j] << "\t]";
		}
  	}

  	cout << endl << endl;
}

void Juego::Esperar(int i) 
{
	moverse[i].wait();
}

void Juego::Liberar()
{
	for (int i=0; i<num_jugadores; i++){
		moverse[i].signal();
	}
}

void funcion (MRef<Juego> Mario, int i) 
{	
	int ant_x=i;
	int ant_y=i;
	
	while (vidas[i]>0) {
		//cout << "soy la hebra " << i << " y tengo " << vidas[i] << " vidas" << endl;
		this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>()));
		//cout << "soy la hebra " << i << " y estoy despierta " << endl;
		
		if (!bloqueados[i]){
			//cout << "soy la hebra " << i << " y no estoy bloqueada " << endl;
			int columna = aleatorio<0,num_jugadores-1>();
			int fila = aleatorio<0,num_jugadores-1>();
			bool movido=Mario->Moverme(i, fila, columna, ant_x, ant_y);
			if (movido){
			
				Mario->MostrarCampo();
					
				ant_x=fila;
				ant_y=columna;
				
				//cout << "Soy la hebra " << i << " y me muevo a " << fila << ", " << columna << endl;
			}
				
		}
		else {
			//cout << n_bloqueados << " BLOQUEADOS !!!! " << endl;
			if (n_bloqueados==num_jugadores){
				n_bloqueados=0;
				//for (int i=0; i<num_jugadores-1; i++) {
					Mario->Liberar(); //moverse.signal();
					esperando[i]=false;
				//}
				for (int i=0; i<num_jugadores; i++) {
					bloqueados[i]=false;
				}
			}
			else{
				if (esperando[i]) {
					Mario->Esperar(i); //moverse.wait();
					esperando[i]=false;
				}
			}
			
		}
	
	}
	cout << endl << "FIN DEL JUEGO: los jugadores no tienen más vidas " << endl << endl;
	exit(0); // CUANDO TODAS LAS HEBRAS TIENEN 0 VIDAS, SE ACABA EL JUEGO

}

void enemigo (MRef<Juego> Mario) 
{
	while (true){
		this_thread::sleep_for( chrono::milliseconds( aleatorio<100,180>() ));
		int num=aleatorio<0,num_jugadores-1>();
		cout << "Enemigo moviendose por la fila: " << num << endl;
		Mario->EnemigoMover(num);
	}
}

//**********************************************************************
// Funciones

int main() {

	MRef<Juego> Mario = Create<Juego>() ;
	
	thread hebras[num_jugadores];
	
	for (int i=0; i<num_jugadores; i++) {
		hebras[i] = thread (funcion, Mario, i);
	}
	
	thread enemigo_juego(enemigo, Mario);

	for (int i=0; i<num_jugadores; i++) {
		hebras[i].join();
	}
	enemigo_juego.join();
	
	return 0;

}

