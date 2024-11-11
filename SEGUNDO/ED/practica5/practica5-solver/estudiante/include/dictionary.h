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

    Dictionary & operator=(const Dictionary &dictionary);

    class iterator{
    private:
        set<string>::iterator it;
    public:
        iterator(){}
        iterator(const set<string>::iterator& otro):it(otro){}
        iterator(const iterator& otro):it(otro.it){}
        ~iterator(){}
        iterator& operator=(const set<string>::iterator& otro){it=otro;return *this;}
        iterator& operator=(const iterator& otro){it=otro.it;return *this;}
        string operator*()const{return *it;}
        iterator& operator++(){++it;return *this;}
        iterator& operator--(){--it;return *this;}
        iterator& operator++(int){it++;return *this;}
        iterator& operator--(int){it--;return *this;}
        bool operator!=(const iterator& otro){return it != otro.it;}
        bool operator==(const iterator& otro){return it == otro.it;}
    };
    iterator begin(){iterator i = words.begin();return i;}
    iterator end(){iterator i = words.end();return i;}

    class const_iterator{
    private:
        set<string>::const_iterator it;
    public:
        const_iterator(){}
        const_iterator(const set<string>::const_iterator& otro):it(otro){}
        const_iterator(const const_iterator& otro):it(otro.it){}
        ~const_iterator(){}
        const_iterator& operator=(const set<string>::const_iterator& otro){it=otro;return *this;}
        const_iterator& operator=(const const_iterator& otro){it=otro.it;return *this;}
        const string operator*()const{return *it;}
        const_iterator& operator++(){++it;return *this;}
        const_iterator& operator--(){--it;return *this;}
        const_iterator& operator++(int){it++;return *this;}
        const_iterator& operator--(int){it--;return *this;}
        bool operator!=(const const_iterator& otro){return it != otro.it;}
        bool operator==(const const_iterator& otro){return it == otro.it;}
    };
    const_iterator begin() const{const_iterator i = words.begin();return i;}
    const_iterator end() const{const_iterator i = words.end();return i;}

};


#endif  //__DICTIONARY_H__