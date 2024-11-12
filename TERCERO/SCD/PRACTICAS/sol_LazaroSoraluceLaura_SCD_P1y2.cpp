//**********************************************************************
// BY LAURA LÁZARO SORALUCE
// DNI: 45350527R
// GRUPO: 1 DGIIM
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

const unsigned num_jugadores = 5; // Número de jugadores
const unsigned num_rondas = 8; // Número de rondas 
bool elegido[num_jugadores] = {false, false, false, false, false}; // Indica si todos los jugadores han elegido ya la casilla donde creen que está el corazón
int num_elegidos = 5; // Indica el número de jugadores que ya han elegido la casilla donde creen que está el corazón
int total[num_jugadores] = {0,0,0,0,0}; // Número de puntos totales que tiene cada jugador en cada momento del juego
//int mirado[num_jugadores] = {-1,-1,-1,-1,-1}; // Posición concreta a la que ha mirado cada jugador en cada ronda
bool jugar = false; // Indica si los jugadores pueden jugar o deben seguir esperando
int ranking[num_jugadores]={-1,-1,-1,-1,-1};
int orden=0;
int correctos[num_jugadores]={-1,-1,-1,-1,-1};
//int posicion=-1;
int veces = 0;
bool fin=false;
bool esperando[num_jugadores]={false,false,false, false, false}; // Dice si las hebras bloqueadas están pendientes de que se les haga wait


//**********************************************************************
// Monitor

class Juego : public HoareMonitor
{
 private:
 int campo[4];
 int mirado[num_jugadores];

 CondVar             // colas condicion:
	mirar[num_jugadores];

 public:                    // constructor y métodos públicos
   Juego() ;             // constructor
   void Mirar(int x, int pos);                
   void EnemigoMover(int num);
   void Liberar();
   void Esperar(int x);
   void MostrarCampo();
   void CampoInicial();
   void RecuentoPuntos(int pos);
   void PonerCorazon(int pos);
} ;

Juego::Juego() 
{

	for (int i=0;i<num_jugadores; i++){
		mirar[i] = newCondVar();
		mirado[i]=-1;
	}
	for (int i=0; i<4; i++) {
		campo[i]=0;
	}
}

void Juego::Mirar(int x, int pos)
{
	mirado[x]=pos;
}

void Juego::CampoInicial() 
{
	for (int i=0; i<4; i++) {
		campo[i]=0;
	}
	for (int i=0; i<num_jugadores; i++){
		mirado[i]=-1;
	}
}

void Juego::PonerCorazon(int pos) {
	campo[pos]=1;
}

void Juego::Liberar()
{
	for (int i=0; i<num_jugadores; i++){
		mirar[i].signal();
	}
}

void Juego::Esperar(int i) 
{
	mirar[i].wait();
}

void Juego::RecuentoPuntos(int pos)
{
	/*for (int i=0; i<num_jugadores; i++){
		if (mirado[i]==pos){
			correctos[i]=ranking[i];
		}
	}*/
}

void hebra_jugador(MRef<Juego> Mario, int i) 
{
	
	while (!fin) 
	{
		
		if (!elegido[i] && jugar){
			int pos = aleatorio<0,3>();
			
			Mario->Mirar(i, pos);

			
			cout << "soy la hebra " << i << " y elijo la posicion " << pos << endl;
			
			num_elegidos++;
			cout << "num elegidos " << num_elegidos << endl << endl;
			elegido[i]=true;
			cout << "soy la hebra " << i << " y he elegido " << endl;
			

		}
		else {
			if (num_elegidos==num_jugadores && jugar){
				Mario->Liberar();
				esperando[i]=false;
			}
			else if (num_elegidos<num_jugadores) {
				if (esperando[i]) {
					Mario->Esperar(i);
					esperando[i]=false;
				}
			}
		}
		
	}
	
	exit(0);
}

void hebra_npc (MRef<Juego> Mario) 
{
	
	while (veces<num_rondas){
		if (num_elegidos == num_jugadores) {
		
			jugar=false;

			
			Mario->CampoInicial();
		
			int pos = aleatorio<0,3>();
			
			Mario->PonerCorazon(pos);
			
			cout << "CORAZON PUESTO EN: " << pos << endl << endl;
			
			num_elegidos = 0;
			
			for (int i=0; i<num_jugadores; i++) {
					elegido[i]=false;
				}
			
			jugar = true;
		
			veces++;
		}
		
	}
	fin =true;
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
	
	thread npc(hebra_npc, Mario);

	for (int i=0; i<num_jugadores; i++) {
		hebras_jugadores[i].join();
	}
	npc.join();
	
	return 0;

}

