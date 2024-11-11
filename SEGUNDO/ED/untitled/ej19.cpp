//
// Created by lauralazaro on 27/11/21.
//

#include <stack>
#include <iostream>
using namespace std;

/**
 * @brief Función que elimina los elementos consecutivos que están repetidos en una pila
 * @param p pila que se va a transformar
 * @post la pila puede verse o no modificada, dependiendo de si tiene o no valores consecutivos repetidos
 */
void transformarpila(stack<int> &p) {
    int size = p.size();
    int anterior = p.top();
    p.pop();
    stack<int> aux;
    aux.push(anterior);

    for (int i=1; i<size; i++) {
        if (p.top() == anterior)
            p.pop();
        else {
            anterior = p.top();
            aux.push(anterior);
            p.pop();
        }
    }

    p=aux;
}

int main () {

    stack<int> pila;
    int aux[] = {1,1,2,3,3,4,5,5,1,1,9,8,7,7,3};

    for (int i=0; i<15; i++)
        pila.push(aux[i]);

    transformarpila(pila);

    while(!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }

    return 0;
}