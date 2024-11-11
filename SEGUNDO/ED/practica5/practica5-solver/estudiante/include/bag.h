/**
 * @file bag.h
 * @brief TDA Bag e implementación
 * @author María Cribillés y Laura Lázaro
 */

#ifndef __BAG_H__
#define __BAG_H__
#include <vector>
#include <cstdlib>
#include "letters_set.h"

using namespace std;

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>

class Bag {
private:
    vector<T> v;
public:
    /**
     * Constructor por defecto
     */
    Bag() {
    }

    /**
     * Constructor de copia
     * @param other Objeto que vamos a copiar
     * @post El vector se ve modificado si el vector de other no está vacio
     */
    Bag(const Bag<T> &other) {
        v = other.v;
    }

    /**
     * @brief Añade un elemento a la bolsa
     * @param element elemento de tipo T que se añade a la bolsa
     * @post El vector se ve modificado, su tamaño aumenta en 1
     */
    void add(const T & element) {
        v.push_back(element);
    }

    /**
     * @brief Extrae un elemento aleatorio de la bolsa, lo elimina de esta
     * @pre La bolsa no puede estar vacía
     * @return El elemento aleatorio que se ha extraido y eliminado
     * @post El vector se ve modificado, su tamaño disminuye en 1
     */
    T get() {
        int random = rand() % v.size();
        T element = v.at(random);
        v.at(random) = v.back();
        v.pop_back();

        return element;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa
     * @post El vector se ve modificado, si no estaba vacío
     */
    void clear() {
        v.clear();
    }

    /**
     * @brief Indica el tamaño de la bolsa
     * @return El número de elementos que hay en el vector
     * @post El vector no se ve modificado
     */
    unsigned int size() const {
        return v.size();
    }

    /**
     * @brief Comprueba si la bolsa está vacía
     * @return Un bool que indica si la bolsa está vacía o no
     * @post El vector no se ve modificado
     */
    bool empty() {
        return v.empty();
    }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Objeto que se va a copiar
     * @return Referencia al objeto actual
     * @post El vector se ve modificado si other no es vacío
     */
    const Bag<T> & operator= (const Bag<T> &other) {
        v=other.v;
        return *this;
    }
};

#endif
