/**
   @file Algoritmo obvio vector ordenado
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

inline static
bool ordenar(int vector[], int num_elem);

bool ordenar(int vector[], int num_elem) {
	bool found = false;
	for (int i=0; i<num_elem && !found; i++) {
		if (vector[i]==i) {
			cout << i << endl;
			found = true;
		}
		else if (vector[i]>i)
			i=vector[i]-1;
	}
	return found;
}

int main() {
	int v[10];
	for (int i=0; i<4; i++) {
		v[i]=i;
	}
	ordenar(v, 4);
	
	for (int i=0; i<9; i=i+2) {
		v[i]=4;
	}
	ordenar(v, 10);
}
