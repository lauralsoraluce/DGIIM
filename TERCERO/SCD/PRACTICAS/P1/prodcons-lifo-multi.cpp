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

const unsigned 
   num_items = 40 ,   // número de items
	tam_vec   = 10 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)
   int vec[tam_vec]={0}; // vector intermedio
   int primera_libre = 0;
   const int num_productoras = 4;
   int cada_prod = num_items/num_productoras;
   const int num_consumidoras = 5;
   int cada_cons = num_items/num_consumidoras;
   unsigned producidos[num_productoras] = {0};
   
   Semaphore libres(tam_vec), ocupadas(0), contador(1);

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato(int num_hebra)
{

   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = num_hebra*cada_prod+producidos[num_hebra] ;
   producidos[num_hebra]++ ;
   cont_prod[dato_producido] ++ ;
   cout << "La hebra " << num_hebra << " ha producido: " << dato_producido << endl << flush ;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato, int num_hebra)
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora( int num_hebra )
{
   for( unsigned i = 0 ; i<cada_prod; i++ )
   {
      int dato = producir_dato(num_hebra) ;
      
      sem_wait( libres );
      sem_wait( contador ); // Cuando esta hebra esté modificando el valor de primera_libre, la otra no podrá modificarlo a la vez.
      if (primera_libre<tam_vec) {
      	vec[primera_libre]=dato;
     	primera_libre++;
      }
      cout << "Se ha insertado el valor " << dato << " en el buffer" << endl;
      sem_signal( contador );
      sem_signal( ocupadas );
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( int num_hebra )
{
   for( unsigned i = num_hebra*cada_cons ; i < (num_hebra*cada_cons + cada_cons) ; i++ )
   {
      int dato ;
      
      sem_wait ( ocupadas );
      sem_wait ( contador ); // Cuando esta hebra esté modificando el valor de primera_libre, la otra no podrá modificarlo a la vez.
      if (primera_libre>-1 && primera_libre<tam_vec) {
      	primera_libre--;
      	dato = vec[primera_libre];
      	cout << "Se ha extraído el valor " << dato << " del buffer" << endl;   
      }   
      sem_signal( contador );
      sem_signal( libres );
      consumir_dato( dato, num_hebra) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora0 ( funcion_hebra_productora, 0),
   		  hebra_productora1 ( funcion_hebra_productora, 1 ),
   		  hebra_productora2 ( funcion_hebra_productora, 2 ),
   		  hebra_productora3 ( funcion_hebra_productora, 3 ),
          hebra_consumidora0 ( funcion_hebra_consumidora, 0 ),
          hebra_consumidora1 ( funcion_hebra_consumidora, 1 ),
          hebra_consumidora2 ( funcion_hebra_consumidora, 2 ),
          hebra_consumidora3 ( funcion_hebra_consumidora, 3 ),
          hebra_consumidora4 ( funcion_hebra_consumidora, 4 );

   hebra_productora0.join() ;
   hebra_productora1.join() ;
   hebra_productora2.join() ;
   hebra_productora3.join() ;
   hebra_consumidora0.join() ;
   hebra_consumidora1.join() ;
   hebra_consumidora2.join() ;
   hebra_consumidora3.join() ;
   hebra_consumidora4.join() ;

   test_contadores();
}
