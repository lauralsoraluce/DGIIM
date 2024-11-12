// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
	num_jugadores=3,
	id_peach=0,
	id_mario=1,
	id_npc=2,
   etiq_liberar = 3,
   etiq_gas1 = 1,
   etiq_gas2 = 2,
   etiq_gas0 = 0;


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------

void funcion_comedor( int id)
{
  int num_rec, peso;
  string name;
  MPI_Status estado;
  
  if (id == id_peach) name="Peach";
  else if (id==id_mario) name="Mario";

  while ( true )
  {
  	MPI_Probe( id_npc, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
	MPI_Get_count( &estado, MPI_INT, &num_rec );
	// reservar memoria para el mensaje y recibirlo
	int buffer[num_rec];
	MPI_Recv(buffer, num_rec, MPI_INT, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
	
	
	cout << name << " ha recibido " << num_rec << " tartacas que pesan: " << buffer[0];
	if (num_rec==2) cout << " y " << buffer[1];
	cout << endl;
	
	peso=0;
	
	for (int i=0; i<num_rec; i++) {
		peso+=buffer[i];
	}
	
	sleep_for( milliseconds( aleatorio<10,100>() ) );
    
    	cout << name << " ha terminado de comerse sus tartacas " << endl;
	
	MPI_Ssend(&peso, 1, MPI_INT, id_npc, 0, MPI_COMM_WORLD);
  	
    
 }
}
// ---------------------------------------------------------------------

void funcion_npc( int id )
{
  int valor ;  // valor recibido, identificador del filósofo
  MPI_Status estado;
  int num_tartas;
  int suma_comida[2]={0,0};
  int id_aceptable;
  

  while ( true )
  {
  	//int pesos_tartas[2]={aleatorio<50,150>(),aleatorio<50,150>());
  	
  	num_tartas = aleatorio<1,2>();
  	
  	int pesos_tartas[num_tartas];
  	for (int i=0; i<num_tartas; i++){
  		pesos_tartas[i]=aleatorio<50,150>();
  		//suma_comida[0]+=pesos_tartas[i];
  	}

  	MPI_Ssend(&pesos_tartas, num_tartas, MPI_INT, id_peach, 0, MPI_COMM_WORLD);
  	
  	
  	num_tartas = aleatorio<1,2>();
  	for (int i=0; i<num_tartas; i++){
  		pesos_tartas[i]=aleatorio<50,150>();
  		//suma_comida[1]+=pesos_tartas[i];
  	}
  	MPI_Ssend(&pesos_tartas, num_tartas, MPI_INT, id_mario, 0, MPI_COMM_WORLD);
  	
  	id_aceptable=MPI_ANY_SOURCE;
  	MPI_Recv(&valor, 1, MPI_INT, id_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
  	if (estado.MPI_SOURCE == id_peach) {
  		id_aceptable=id_mario;
  		suma_comida[0]=valor;
  	}
  	else {
  		id_aceptable=id_peach;
  		suma_comida[1]=valor;
  	}
  	MPI_Recv(&valor, 1, MPI_INT, id_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
  	if (estado.MPI_SOURCE == id_peach) {
  		suma_comida[0]=valor;
  	}
  	else {
  		suma_comida[1]=valor;
  	}
  	
	if (suma_comida[0]>suma_comida[1]) 
		cout << "PEACH ES LA GORDA PORQUE COMIÓ: " << suma_comida[0] << " KG " << endl;
	else 
		cout << "MARIO ES EL GORDO PORQUE COMIÓ: " << suma_comida[1] << " KG" << endl;
  	
  }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_jugadores == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio == id_npc )          
         funcion_npc( id_propio ); //   es la gasolinera
      else {                
         funcion_comedor( id_propio); //   es un coche
      }
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_jugadores << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
