/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author Laura Lázaro Soraluce
 */

#include "maxqueue.h"

int MaxQueue::Size() const {
    return pila.size();
}

bool MaxQueue::Empty() const {
    return pila.empty();
}

datos MaxQueue::Front() const {
    return pila.top();
}

void MaxQueue::Pop() {
    pila.pop();
}

void MaxQueue::Push(int elemento) {
    stack<datos> pilaAux;
    datos aux {elemento, elemento};

    if (Empty()) {
        pila.push(aux); // Si la cola está vacía, el máximo es el del elemento que vamos a meter, ya que es el único.
    }
    else {
        while (!Empty()) {
            pilaAux.push(Front());
            Pop();
        }
        /* Volcamos todos los elementos de la pila original en una auxiliar, para poder tener los elementos ordenados
            al contrario. */

        pila.push(aux);
        /* Metemos el nuevo elemento en la pila original, así será el último en salir, y actuará como si estuviese en
            el back de la cola. */

        while (!pilaAux.empty()) {
            if (pila.top().max > pilaAux.top().max) {
                pilaAux.top().max = pila.top().max;
            }
            pila.push(pilaAux.top());
            pilaAux.pop();
        }
        /* Para cada uno de los elementos de la pila auxiliar (los que estaban antes del nuevo elemento), vamos
            comparando su máximo con el del último elemento metido en la pila original. Si el máximo del elemento que
            vamos a meter en la pila original es menor que el máximo del que está en su tope, actualizamos el máximo
            del elemento que vamos a meter, pues hay elementos en la cola que son mayores y que van a salir más tarde
            que él. */
    }
}

ostream & operator<< (ostream & flujo, datos element) {
    flujo << element.value << "," << element.max << endl;
}