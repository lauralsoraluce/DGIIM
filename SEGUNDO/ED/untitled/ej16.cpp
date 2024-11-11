//
// Created by lauralazaro on 27/11/21.
//
#include <stack>
#include <iostream>

using namespace std;

/**
 * @brief Función que inserta un entero en una posición dada de la lista
 * @pre la posición en la que se va a insertar el entero tiene que ser >=0 y <=size
 * @param a entero a insertar
 * @param pos posición en la que se va a insertar el entero
 * @param pila pila en la que se va a hacer la inserción
 * @post la pila se ve modificada
 */
void insertar(int a, int pos, stack<int> &pila) {
    stack<int> aux;
    int size = pila.size();

    if (pos >= 0 && pos <= size) {
        for (int i = 0; i < pos; i++) {
            aux.push(pila.top());
            pila.pop();
        }
        aux.push(a);

        while (!pila.empty()) {
            aux.push(pila.top());
            pila.pop();
        }

        while(!aux.empty()) {
            pila.push(aux.top());
            aux.pop();
        }
    }
}

/**
 * @brief Función que elimina el entero en una posición dada de la lista
 * @pre la posición del entero que se va a eliminar tiene que ser >=0 y <size
 * @param pos posición en la que se va a insertar el entero
 * @param pila pila en la que se va a hacer la inserción
 * @post la pila se ve modificada
 */
void borrar(int pos, stack<int> &pila) {

    stack<int> aux;
    int size = pila.size();

    if (pos >=0 && pos<size) {
        for (int i = 0; i < pos; i++) {
            aux.push(pila.top());
            pila.pop();
        }
        pila.pop();
        for (int i = (pos + 1); i < size; i++) {
            aux.push(pila.top());
            pila.pop();
        }

        while (!aux.empty()) {
            pila.push(aux.top());
            aux.pop();
        }
    }
}

int main() {

    stack <int> P;

    for (int i=10; i>0; i--)
        P.push(i); // La pila queda top->1,2,3,4,5,6,7,8,9,10

    insertar(3,4,P);

    cout << "TRAS INSERTAR: ";

    while (!P.empty()) {
        cout << P.top() << " ";
        P.pop();
    }

    cout << endl;

    ///////////////////////////////////////////////////////////

    for (int i=10; i>0; i--)
        P.push(i);

    borrar(6, P);

    cout << "TRAS BORRAR: ";

    while (!P.empty()) {
        cout << P.top() << " ";
        P.pop();
    }

    cout << endl;

    return 0;
}