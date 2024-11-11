//
// Created by lauralazaro on 27/11/21.
//
#include <queue>
#include <iostream>

using namespace std;

/**
 * @brief Función que coloca los primeros elementos impares de una cola al final de esta. Es decir, todos los elementos
 *          hasta llegar al primer elemento par, que pasa a ser el frente de la cola.
 * @param p cola sobre la que se va a hacer la rotación
 * @post La cola se ve modificada si hay elementos pares e impares. Si sólo hay impares o sólo pares, no.
 */
void rotacion(queue <int> &c) {
    int size = c.size();
    int counter = 0;
    /* Contador para que si se recorre la cola entera sin encontrar un número
    	par, se deja la cola como la original. */

    while ((c.front()%2)!=0 && counter<size) {
        c.push(c.front());
        c.pop();
        counter++;
    }
}

int main() {
    queue <int> cola;
    int aux[]={1,3,5,2,4};
    for (int i=0; i<5; i++)
        cola.push(aux[i]);

    rotacion(cola);

    while(!cola.empty()){
        cout << cola.front() << " ";
        cola.pop();
    }

    return 0;
}