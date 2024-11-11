/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author María Cribillés y Laura Lázaro
 */


#ifndef _MAXQUEUE_H_
#define _MAXQUEUE_H_

#include <stack>
#include <iostream>
using namespace std;

struct datos {
    int max; // Current max value in the structure
    int value; // Current value to store
};

class MaxQueue {
    /**
       @page representación de una cola
     **/

private:
    /**
     @brief una pila de la stl de datos (struct)
     **/
    stack<datos> pila;

public:
    /**
    * @brief Indica el tamaño de la cola.
    * @return El número de elementos de elementos de la cola.
    * @post La cola no se modifica.
    */
    int Size() const;

    /**
    * @brief Indica si la cola está vacía.
    * @return Un bool indicando si la cola está vacía.
    * @post La cola no se modifica.
    */
    bool Empty() const;

    /**
    * @brief Accede al frente de la cola.
    * @return El struct datos que está en el frente de la cola.
    * @post La cola no se modifica.
    */
    datos Front() const;

    /**
    * @brief Saca el elemento del frente de la cola sin devolverlo.
    * @pre La cola no puede estár vacía.
    * @post El tamaño de la cola se reduce en 1.
    */
    void Pop();

    /**
    * @brief Añade un elemento a la cola.
    * @param elemento Número que se quiere introducir en el frente de la cola.
    * @post El tamaño de la cola aumenta en 1.
    */
    void Push(int elemento);

    friend ostream & operator<< (ostream & flujo, datos element);
};

ostream & operator<< (ostream & flujo, datos element);

#endif _MAXQUEUE_H_
