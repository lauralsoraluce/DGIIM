#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 

const int num_fumadores = 3 ;


// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SC, multiples prod/cons

class Fumadores : public HoareMonitor
{
 private:
 bool
 	 mostrador_libre; 
 int
 	ingr_mesa;

 CondVar                    // colas condicion:
   ingr_disp[num_fumadores],                //  cola donde espera el consumidor (n>0)
   mostr_vacio ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   Fumadores() ;             // constructor
   void obtenerIngrediente(int i);                // extraer un valor (sentencia L) (consumidor)
   void ponerIngrediente( int i ); // insertar un valor (sentencia E) (productor)
   void esperarRecogidaIngrediente();
} ;

//-------------------------------------------------------------------------
Fumadores::Fumadores(  )
{
	mostr_vacio        = newCondVar();
   for (int i=0; i<num_fumadores; i++) {
   	ingr_disp[i] = newCondVar();
   }
   
   mostrador_libre=true;
   ingr_mesa=-1;
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void Fumadores::obtenerIngrediente( int ingre )
{
   if (ingr_mesa!=ingre)
   		ingr_disp[ingre].wait();
   		
   cout << "retirado ingrediente: " << ingre << endl;
   // señalar al productor que hay un hueco libre, por si está esperando
   mostr_vacio.signal();
   mostrador_libre=true;
   ingr_mesa=-1;

}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void Fumadores::ponerIngrediente( int ingre )
{
   if (!mostrador_libre)
   		mostr_vacio.wait();
   		
   		
   
   cout << "puesto ingrediente: " << ingre << endl;
   // señalar al productor que hay un hueco libre, por si está esperando
   ingr_disp[ingre].signal();
   mostrador_libre=false;
   ingr_mesa=ingre;
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void Fumadores::esperarRecogidaIngrediente( )
{
   
   if (mostrador_libre)
   		mostr_vacio.signal();

}

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef<Fumadores>  Estanco )
{
	while (true)
	{
		int i = producir_ingrediente();
		Estanco->ponerIngrediente(i);
		Estanco->esperarRecogidaIngrediente();
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( MRef<Fumadores>  Estanco, int num_fumador )
{
	
   while( true )
   {
   		Estanco->obtenerIngrediente(num_fumador);
		//sem_wait ( ingr_disp[num_fumador] );
		//cout << "retirado ingrediente: " << num_fumador << endl;
		
		//sem_signal (mostr_vacio);
		fumar(num_fumador);
	
   }
}

//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los fumadores." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;
   
   MRef<Fumadores> Estanco = Create<Fumadores>() ;
   
   thread hebra_fumador[num_fumadores];
   thread hebra_estanquero;
      
   hebra_estanquero= thread ( funcion_hebra_estanquero, Estanco );
   for (int i=0; i<num_fumadores; i++)
   	hebra_fumador[i] = thread (funcion_hebra_fumador, Estanco, i);
   
   hebra_estanquero.join() ;

   for (int i=0; i<num_fumadores; i++)
   	hebra_fumador[i].join();
}
