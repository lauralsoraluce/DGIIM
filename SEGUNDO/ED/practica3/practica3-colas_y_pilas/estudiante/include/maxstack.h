/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author María Cribillés y Laura Lázaro
 */

#ifndef _MAXSTACK_H_
#define _MAXSTACK_H_

#include <queue>
#include <iostream>
using namespace std;

struct datos {
    int max; // Current max value in the structure
    int value; // Current value to store
};

class MaxStack {
    /**
      @page repersentación de una pila
    **/

private:
    /**
      @brief una cola de la stl de datos (struct)
    **/
    queue<datos> cola;

public:
    /**
    * @brief Indica el tamaño de la pila.
    * @return El número de elementos de la pila.
    * @post La pila no se modifica.
    */
    int Size() const;

    /**
    * @brief Indica si la pila está vacía.
    * @return Un bool indicando si la pila está vacía.
    * @post La pila no se modifica.
    */
    bool Empty() const;

    /**
    * @brief Accede al tope de la pila.
    * @return El struct datos que está en el tope de la pila.
    * @post La pila no se modifica.
    */
    datos Top() const;

    /**
    * @brief Saca el elemento del tope de la pila sin devolverlo.
    * @pre La pila no puede estár vacía.
    * @post El tamaño de la pila se reduce en 1.
    */
    void Pop();

    /**
    * @brief Añade un elemento a la pila.
    * @param elemento Número que se quiere introducir en el tope de la pila.
    * @post El tamaño de la pila aumenta en 1.
    */
    void Push(int elemento);

    friend ostream & operator<< (ostream & flujo, datos elemento);
};

ostream & operator<< (ostream & flujo, datos elemento);

#endif _MAXSTACK_H_