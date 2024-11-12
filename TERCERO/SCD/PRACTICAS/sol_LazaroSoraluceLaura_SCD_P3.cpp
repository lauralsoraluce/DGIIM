// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI

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
	num_jugadores=4,
	id_peach=0,
	id_mario=1,
	id_npc=2,
	id_impresor=3,
	rondas = 4;


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

void imprimir(const string & cadena) //Para mostrar los mensajes en el orden en el que se mandan
{
	MPI_Ssend(cadena.c_str(), cadena.length(), MPI_CHAR, id_impresor, 0, MPI_COMM_WORLD);
}
// ---------------------------------------------------------------------

void impresor(int id) //Para mostrar los mensajes en el orden en el que se mandan
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

void funcion_jugador( int id)
{
  int num_rec; //num de tartas recibidas
  int peso; //peso total de las tartas recibidas
  int porcion; // peso de la porcion comida
  string name; // nombre del jugador
  MPI_Status estado;
  
  //Asignamos el nombre correspondiente al jugador
  if (id == id_peach) name="Peach";
  else if (id==id_mario) name="Mario";

  while ( true )
  {
  	MPI_Probe( id_npc, MPI_ANY_TAG, MPI_COMM_WORLD, &estado ); //Esperamos mensaje de Yoshi
	MPI_Get_count( &estado, MPI_INT, &num_rec ); //Cuando lo haya
	// reservar memoria para el mensaje y recibirlo
	int buffer[num_rec];
	MPI_Recv(buffer, num_rec, MPI_INT, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado ); //Recibimos el mensaje
	
	
	//Mostramos un mensaje u otro dependiendo del número de tartas recibidas
	if (num_rec==1) { 
		imprimir(name + " ha recibido " + to_string(num_rec) + " tarta que pesa: " + to_string(buffer[0]));
	}
	else if (num_rec==2) {
		imprimir(name + " ha recibido " + to_string(num_rec) + " tartas que pesan: " + to_string(buffer[0]) + " y " + to_string(buffer[1]));
	}
	
	peso=0;
	
	//Calculamos el peso total de las tartas recibidas por el jugador
	for (int i=0; i<num_rec; i++) {
		peso+=buffer[i];
	}
	
	//Calculamos una porción aleatoria de la tarta que ha recibido el jugador
	porcion=random() % peso;
	
	sleep_for( milliseconds( aleatorio<10,100>() ) ); // espera mientras comen
	
    	imprimir(name + " ha terminado de comerse su porcion ");
	
	//Le mandamos a Yoshi la información sobre la porción que el jugador se ha comido
	MPI_Send(&porcion, 1, MPI_INT, id_npc, 0, MPI_COMM_WORLD);
  	
    
 }
}
// ---------------------------------------------------------------------

void funcion_npc( int id )
{
  int valor ;  // guarda en cada recepción los pesos de las porciones que se comieron los jugadores
  MPI_Status estado;
  int num_tartas; // numero de tartas que manda a cada jugador
  int suma_comida[2]={0,0}; //guarda la cantidad de tarta que ha comido cada jugador en la ronda para comparar
  int id_aceptable = MPI_ANY_SOURCE; //id del que puede recibir mensajes en cada momento, se utiliza para saber quién de los dos juadores aún no ha mandado su información en una ronda
  int contador=0; // contador de rondas
  int puntos[2]={0,0}; // puntos de cada jugador
  int hay_mens;
  

  while ( contador<rondas )
  {
  	// Se mandan las tartas a Peach
  	num_tartas = aleatorio<1,2>();
  	
  	int pesos_tartas_P[num_tartas];
  	for (int i=0; i<num_tartas; i++){
  		pesos_tartas_P[i]=aleatorio<1,10>();

  	}
	
	imprimir("Yoshi manda " + to_string(num_tartas) + " a Peach ");
  	MPI_Send(&pesos_tartas_P, num_tartas, MPI_INT, id_peach, 0, MPI_COMM_WORLD);
  	
  	
  	//Se mandan las tartas a Mario
  	num_tartas = aleatorio<1,2>();
  	int pesos_tartas_M[num_tartas];
  	for (int i=0; i<num_tartas; i++){
  		pesos_tartas_M[i]=aleatorio<1,10>();

  	}
  	
  	imprimir("Yoshi manda " + to_string(num_tartas) + " a Mario ");
  	MPI_Send(&pesos_tartas_M, num_tartas, MPI_INT, id_mario, 0, MPI_COMM_WORLD);
  	
  	//espera aleatoria
  	sleep_for( milliseconds( aleatorio<10,100>() ) );
  	
  	//Pasamos de ronda
  	contador++;
  }
  
  //Se calculan quien se lleva los puntos 
  for (int i=0; i<rondas; i++) {
  	MPI_Recv(&valor, 1, MPI_INT, id_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
  	if (estado.MPI_SOURCE == id_peach) {
  		id_aceptable=id_mario; // si el primer mensaje lo mandó peach, esperamos uno de mario
  		suma_comida[0]=valor;
  	}
  	else {
  		id_aceptable=id_peach; // si el primer mensaje lo mandó mario, esperamos uno de peach
  		suma_comida[1]=valor;
  	}
  	
  	MPI_Recv(&valor, 1, MPI_INT, id_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
  	if (estado.MPI_SOURCE == id_peach) {
  		suma_comida[0]=valor;
  	}
  	else {
  		suma_comida[1]=valor;
  	}
  	
  	id_aceptable=MPI_ANY_SOURCE;
  	
  	if (suma_comida[0]>suma_comida[1]) 
		puntos[0]++;
	else 
		puntos[1]++;
  	
  }
  
  //mostramos el ganador
  if (puntos[0]>puntos[1]) {
  	imprimir("PEACH es la GANADORA ");
  }
  else if (puntos[1]>puntos[0]){
  	imprimir("MARIO es el GANADOR ");
  }
  else {
  	imprimir("HAY un EMPATE!");
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
         funcion_npc( id_propio ); //   es Yoshi
      else if (id_propio==id_impresor){
      	impresor(id_propio); // es el impresor
      }
      else {                
         funcion_jugador( id_propio); //   es un jugador
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
