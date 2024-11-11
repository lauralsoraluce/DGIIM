#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>

// generador de ejemplos para el problema del elemento en su posici�n. Para rellenar el vector de tama�o n, genera todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; despu�s obtiene una permutaci�n aleatoria de ese vector, se queda con los n primeros elementos, y los ordena de forma creciente

void DyV1 (vector<int> v, int ini, int fin) {

	bool encontrado =false;
	
	while(ini<=fin && !encontrado) {
		int m=(fin+ini)/2;
		if(v[m]==m) {
			//cout << m << endl;
			encontrado=true;
		}
		else if (v[m]<m) {
			ini=m+1;
		}
		else
			fin=m-1;
	}
}

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[])
{
	clock_t tantes;    // Valor del reloj antes de la ejecución
	clock_t tdespues;  // Valor del reloj después de la ejecución

	if (argc != 2)
	{
	   cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	   return -1;
	}

	int n = atoi(argv[1]);
	int m=2*n-1;
	double media = 0;
	
	for (int i=0;i<15;++i) {
	
		int * T = new int[n];
		assert(T);
		int * aux = new int[m];
		assert(aux);

		//genero todos los enteros entre -(n-1) y n-1
		for (int j=0; j<m; j++) aux[j]=j-(n-1);

		//algoritmo de random shuffling the Knuth (permutaci�n aleatoria) 
		for (int j=m-1; j>0; j--) {
		   double u=uniforme();
		   int k=(int)(j*u);
		   int tmp=aux[j];
		   aux[j]=aux[k];
		   aux[k]=tmp;
		}
		//me quedo con los n primeros del vector
		for (int j=0; j<n; j++) T[j]=aux[j];

		//Y ahora ordeno el vector T
		vector<int> myvector (T, T+n);
		//vector<int>::iterator it;

		sort(myvector.begin(),myvector.end());

		/* for (it=myvector.begin(); it!=myvector.end(); ++it)
		    cout << " " << *it;

		  cout << endl;*/

		delete [] aux;
		
		tantes = clock();
		DyV1(myvector,0,n-1);
		tdespues = clock();
		media += (double)(tdespues-tantes)/CLOCKS_PER_SEC;
	}
	
	cout << n << " " << media/15.0 << endl;
	
	return 0;
}
