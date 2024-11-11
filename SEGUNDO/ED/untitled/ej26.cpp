//
// Created by lauralazaro on 28/11/21.
//

#include <stack>
#include <iostream>

using namespace std;

/**
 * @brief Función que reordena los elementos de una pila para que los pares queden ordenador arriba de los impares,
 *          también ordenados.
 * @param P Pila que vamos a ordenar
 * @post La pila queda modificada si los pares no están ya todos arriba de los impares
 */
void flota_pares(stack<int>&P) {
    stack <int> aux_par;
    stack <int> aux_impar;

    int size_ori=P.size();

    for (int i=0; i<size_ori; i++) {
        if (P.top()%2 == 0)
            aux_par.push(P.top());
        else
            aux_impar.push(P.top());
        P.pop();
    }

    while (!aux_impar.empty()) {
        P.push(aux_impar.top());
        aux_impar.pop();
    }

    while (!aux_par.empty()) {
        P.push(aux_par.top());
        aux_par.pop();
    }
}

int main() {

    stack<int> P;

    int aux[] = {6,24,3,8,3,6,2,1};

    for (int i=0; i<8; i++)
        P.push(aux[i]); // La pila ha quedado: top-> 1,2,6,3,8,3,24,6

    flota_pares(P);

    while(!P.empty()) {
        cout << P.top() << " ";
        P.pop();
    }

    return 0;
}

