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
#include <string>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_surtidores = 5,
   num_coches  = 10 ,
   id_gasolinera = 10,
   id_impresor=11,
   //etiq_gas[3] = {0, 1, 2},
   etiq_liberar = 3,
   etiq_gas1 = 1,
   etiq_gas2 = 2,
   etiq_gas0 = 0,
   num_procesos = num_coches+2;


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

void imprimir(const string & cadena)
{
	MPI_Ssend(cadena.c_str(), cadena.length(), MPI_CHAR, id_impresor, 0, MPI_COMM_WORLD);
}
// ---------------------------------------------------------------------

void funcion_coche( int id, int tipo_gas )
{
  int peticion;
  // string s;

  while ( true )
  {
    // cout <<"Coche " <<id << " solicita surtidor " << tipo_gas << endl;
    // ... solicitar surtidor (completar)
    //s = string("Coche " + to_string(id) + " solicita surtidor " + to_string(tipo_gas));
    imprimir("Coche " + to_string(id) + " solicita surtidor " + to_string(tipo_gas));
    MPI_Ssend(&peticion, 1, MPI_INT, id_gasolinera, tipo_gas, MPI_COMM_WORLD);

    imprimir("Coche " + to_string(id) + " comienza a repostar ");
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    imprimir("Coche " + to_string(id) + " libera surtidor " + to_string(tipo_gas));
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&tipo_gas, 1, MPI_INT, id_gasolinera, etiq_liberar, MPI_COMM_WORLD);
    
    imprimir("Coche " + to_string(id) + " comienza a conducir ");
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_gasolinera( int id )
{
  int valor ;  // valor recibido, identificador del filósofo
  MPI_Status estado1, estado2 ;       // metadatos de las dos recepciones
  int total_libres = 5;
  int etiq_emisor_aceptable;
  int libres[3]={2, 1, 2};
  int hay_mens;
  bool mens = false;

  while ( true )
  {
  	
  	MPI_Iprobe(MPI_ANY_SOURCE, etiq_liberar, MPI_COMM_WORLD, &hay_mens, &estado1 );
  	if (hay_mens){
  		mens=true;
  		MPI_Recv ( &valor, 1, MPI_INT, estado1.MPI_SOURCE, etiq_liberar, MPI_COMM_WORLD,&estado2 );
  		libres[valor]++;
  	}
  	
  	MPI_Iprobe(MPI_ANY_SOURCE, etiq_gas0, MPI_COMM_WORLD, &hay_mens, &estado1 );
  	if (hay_mens && libres[0]>0){
  		mens=true;
  		MPI_Recv ( &valor, 1, MPI_INT, estado1.MPI_SOURCE, etiq_gas0, MPI_COMM_WORLD,&estado2 );
  		libres[0]--;
  	}
  	
  	MPI_Iprobe(MPI_ANY_SOURCE, etiq_gas1, MPI_COMM_WORLD, &hay_mens, &estado1 );
  	if (hay_mens && libres[1]>0){
  		mens=true;
  		MPI_Recv ( &valor, 1, MPI_INT, estado1.MPI_SOURCE, etiq_gas1, MPI_COMM_WORLD,&estado2 );
  		libres[1]--;
  	}
  	
  	MPI_Iprobe(MPI_ANY_SOURCE, etiq_gas2, MPI_COMM_WORLD, &hay_mens, &estado1 );
  	if (hay_mens && libres[2]>0){
  		mens=true;
  		MPI_Recv ( &valor, 1, MPI_INT, estado1.MPI_SOURCE, etiq_gas2, MPI_COMM_WORLD,&estado2 );
  		libres[2]--;
  	}
  	
  	/*for (int i=0; i<3; i++) {
  		if (libres[i]>0) {
  			MPI_Iprobe(MPI_ANY_SOURCE, etiq_gas[i], MPI_COMM_WORLD, &hay_mens, &estado1);
  			if (hay_mens){
  				MPI_Recv(&valor, 1, MPI_INT, estado1.MPI_SOURCE, etiq_gas[i], MPI_COMM_WORLD, &estado2);
  				libres[i]--;
  			}
  		}
  	}*/
  	
  	if (!mens) {
  		sleep_for( milliseconds(20) );
  		mens=false;
  	}
  }
}
// ---------------------------------------------------------------------

void impresor(int id)
{
	//int valor;
	MPI_Status estado;
	int num_chars_rec;
	
	while (true)
	{
		MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
		MPI_Get_count( &estado, MPI_CHAR, &num_chars_rec );
		// reservar memoria para el mensaje y recibirlo
		char * buffer = new char[num_chars_rec+1] ;
		MPI_Recv( buffer, num_chars_rec, MPI_CHAR, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
		buffer[num_chars_rec] = 0 ; // añadir un cero al final
		
		cout << buffer << endl;
		delete[] buffer;
		
		
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
      if ( id_propio == id_gasolinera )          
         funcion_gasolinera( id_propio ); //   es la gasolinera
      else if (id_propio == id_impresor){  
         impresor(id_propio);    
      }
      else {          
         int tipo_gas = aleatorio<0,2>();
         funcion_coche( id_propio, tipo_gas ); //   es un coche
      }
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
