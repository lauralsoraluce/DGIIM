/**
 * @file dictionary.h
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 * @author María Cribillés y Laura Lázaro
 */

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Dictionary{

    /**
      @page representacion de un diccionario
    **/
private:
    /**
     @brief dato privado de tipo set de la STL que representa las palabras
   **/
    set <string> words;
public:
    /**
    * @brief Constructor por defecto .
    * @post Genera una instancia de la clase Diccionario vacio
    * @return Diccionario vacio
    */
    Dictionary();

    /**
    * @brief Constructor de copias (crea un Dictionary con el mismo contenido que el que se pasa como argumento)
    * @param other Referencia a un diccionario original que se quiere copiar.
    * @return Dictionary el objeto imagen creado.
    * @post El set se ve modificado si el set de other no es vacío
    */
    Dictionary(const Dictionary & other);

    /**
     * @brief Indica si una palabra esta en el diccionario o no
     * @param val la palabra que se quiere buscar
     * @post el set no se ve modificado
     * @return booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists (const string &val) const;

    /**
     * @brief Inserta una palabra en el diccionario
     * @param val palabra a insertar en el diccionario
     * @post el set se ve modificado si val no estaba ya en él
     * @return booleano que indica si la insercion ha tenido exito. Una palabara se insert con exito si no existia
     * previamente en el diccionario
     */
    bool insert (const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     * @pre El set no puede estar vacío
     * @param val palabra a borrar del diccionario
     * @post El set se ve modificado si val está en el objeto
     * @return booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Elimina todas las palabras contenidas en el conjunto
     * @post El set se ve modificado, si no estaba ya vacío
     */
    void clear();

    /**
     * @brief Comprueba si el diccionario esta vacio
     * @post El set no se ve modificado
     * @return true si el diccionario esta vacio, flase en caso contrario
     */
    bool empty () const;

    /**
     * @brief Tamaño del diccionario
     * @post El set no se ve modificado
     * @return Numero de palabras guardadas en el diccionario
     */
    unsigned int size() const;

    /**
     * @brief Indica el numero de apariciones de una letra
     * @param c letra a buscar
     * @post El set no se ve modificado
     * @return un entero indicando el numero de apariciones
     */
    int getOcurrences(const char c) const;

    /**
     * @brief Cuenta el total de letras de un diccionario
     * @post El set no se ve modificado
     * @return entero con el total de letras
     */
    int getTotalLetters() const;

    /**
     * @brief Devuelve las palabras en el diccionario con una longitudad dada
     * @param lenght longitud de las palabras buscadas
     * @post El set no se ve modificado
     * @return vector de palabras con la longitud deseada
     */
    vector <string> wordsOfLength (int lenght) const;
};


#endif  //__DICTIONARY_H__