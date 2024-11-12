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

const int num_escritores = 4 ;
const int num_lectores = 2;


class LecEsc : public HoareMonitor
{
 private:
 bool
 	 escrib; 
 int
 	n_lec;

 CondVar                    // colas condicion:
	lectura,
	escritura;

 public:                    // constructor y métodos públicos
   LecEsc() ;             // constructor
   void ini_lectura();                
   void fin_lectura();
   void ini_escritura();
   void fin_escritura();
} ;

//-------------------------------------------------------------------------
LecEsc::LecEsc(  )
{
	escritura=newCondVar();	
	lectura=newCondVar();
	
	escrib=false;
	n_lec=0;
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void LecEsc::ini_lectura( )
{
   if (escrib)
   		lectura.wait();
   		
   	n_lec++;
   		
   lectura.signal();

}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void LecEsc::fin_lectura()
{
   n_lec--;
   
   if (n_lec==0)
   	escritura.signal();
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

void LecEsc::ini_escritura(  )
{
   
   if (n_lec>0 || escrib)
	escritura.wait();
	
	escrib=true;

}


void LecEsc::fin_escritura( )
{
   
   escrib=false;
   if (!lectura.empty())
   	lectura.signal();
   else
   	escritura.signal();

}

void lector (int i, MRef<LecEsc> Monitor)
{
	while (true)
	{
		Monitor->ini_lectura();
		cout << "Lector " << i << " está leyendo... " << endl;
		Monitor->fin_lectura();
		cout << "Lector " << i << " ha terminado de leer " << endl;
	}
}

void escritor (int i, MRef<LecEsc> Monitor)
{
	while (true)
	{
		Monitor->ini_escritura();
		cout << "Escritor " << i << " está escribiendo... " << endl;
		Monitor->fin_escritura();
		cout << "Escritor " << i << " ha terminado de escribir " << endl;
	}
}

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los lectores y escritores." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;
   
   MRef<LecEsc> Monitor = Create<LecEsc>() ;
   
   thread hebra_lectora[num_lectores];
   thread hebra_escritora[num_escritores];
   
   for (int i=0; i<num_escritores; i++){
   	hebra_escritora[i]= thread (escritor, i, Monitor);
   }
      
   for (int i=0; i<num_lectores; i++){
   	hebra_lectora[i]= thread (lector, i, Monitor);
   }
   
   for (int i=0; i<num_lectores; i++){
   	hebra_lectora[i].join() ;
   }
   
   for (int i=0; i<num_escritores; i++){
	hebra_escritora[i].join();
   }
   
   
}


