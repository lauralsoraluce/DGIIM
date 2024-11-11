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
   num_surtidores = 5,
   num_coches  = 10 ,
   id_gasolinera = 10,
   etiq_liberar = 0,
   etiq_solicitar = 1,
   num_procesos = num_coches+1;


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

void funcion_coche( int id )
{
  int peticion;

  while ( true )
  {
    cout <<"Coche " <<id << " solicita surtidor" <<endl;
    // ... solicitar surtidor (completar)
    MPI_Ssend(&peticion, 1, MPI_INT, id_gasolinera, etiq_solicitar, MPI_COMM_WORLD);

    cout <<"Coche " <<id <<" comienza a repostar" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    cout <<"Coche " <<id <<" libera surtidor" <<endl;
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&peticion, 1, MPI_INT, id_gasolinera, etiq_liberar, MPI_COMM_WORLD);
    
    cout << "Coche " << id << " comienza a conducir" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_gasolinera( int id )
{
  int valor ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones
  int total_libres = 5;
  int etiq_emisor_aceptable;

  while ( true )
  {
		 if (total_libres==0) {
		 	 etiq_emisor_aceptable = etiq_liberar;
		 }
		 else {
		 	 etiq_emisor_aceptable = MPI_ANY_TAG;
		 }
		 	 
		   // ...... recibir petición de cualquier filósofo (completar)
		   MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_emisor_aceptable, MPI_COMM_WORLD,&estado );
		   
		   
		  switch ( estado.MPI_TAG ){
				case etiq_solicitar:
					total_libres--;
					break;
				case etiq_liberar:
					total_libres++;
			}	
   }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio == 10 )          
         funcion_gasolinera( id_propio ); //   es la gasolinera
      else                               
         funcion_coche( id_propio ); //   es un coche
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
