/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author Laura Lázaro Soraluce
 */

#include "maxstack.h"

int MaxStack::Size() const {
    return cola.size();
}

bool MaxStack::Empty() const {
    return cola.empty();
}

datos MaxStack::Top() const {
    return cola.front();
}

void MaxStack::Pop() {
    cola.pop();
}

void MaxStack::Push(int elemento) {
    queue<datos> colaAux;
    datos aux {elemento, elemento};

    if (Empty()) {
        cola.push(aux); // Si la pila está vacía, el máximo es el del elemento que vamos a meter, ya que es el único.
    }
    else {
        if (aux.max < Top().max) {
            aux.max = Top().max;
        }
        /* Si ya hay elementos en la pila, comparamos el elemento que vamos a meter con el máximo del elemento que
            está en el tope, ya que si este último es mayor, el máximo del nuevo elemento deberá ser ese máximo,
            pues en la pila hay elementos más grandes que el nuevo elemento que van a salir más tarde que este. */

        colaAux.push(aux);
        /* Metemos el nuevo elemento ya con su máximo correcto en la cola auxiliar, así estará en el frente y saldrá
            primero, actuando como el tope de la pila. */

        while (!Empty()) {
            colaAux.push(Top());
            Pop();
        }
        /* Volcamos el resto de elementos en la cola auxiliar, para que salgan después del elemento nuevo, como
            ocurriría en una pila, pues ha sido el último en entrar. */

        cola = colaAux;
    }
}

ostream & operator<<(ostream & flujo, datos element) {
    flujo << element.value << "," << element.max << endl;
}