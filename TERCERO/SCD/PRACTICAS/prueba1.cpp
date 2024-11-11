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
   int n = 0;
   Semaphore proceso0(1);
   Semaphore proceso1(0);
   
   
void consumir_dato( )
{
   sem_wait( proceso0 );
   n++;
   sem_signal( proceso0 );
   
   if (n==2) {
   	cout << "Hola soy el proceso " << n << " y estoy activando al otro " << endl;
   	sem_wait( proceso0 );
   	n=0;
   	sem_signal( proceso0 );
   	sem_signal( proceso1 );
   }
   else {
   	cout << "Hola soy el proceso " << n << " y estoy esperando " << endl;
   	sem_wait(proceso1);
   }
  cout << "aaaaaaaaaa" << endl;

}

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;


thread hebra_productora[3];
thread hebra_consumidora[3];

for (int i=0; i<3; i++){
    hebra_productora[i] = thread ( consumir_dato );
    hebra_consumidora[i] = thread ( consumir_dato );
          }

for (int i=0; i<3; i++){
    hebra_productora[i].join();
    hebra_consumidora[i].join();
          }
   //hebra_productora.join() ;
   //hebra_consumidora.join() ;

}
