/**
 * @file letters_set.h
 * @brief TDA LettersSet
 * @details Almacena las letras disponibles para la partida, junto con su información (repeticiones
 * y puntuación), y permite iterar sobre ellas.
 * @author María Cribillés y Laura Lázaro
 */

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__
#include <map>
#include <string>
#include <iostream>

using namespace std;
/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo {
    int repetitions;
    int score;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

class LettersSet{
private:
    map <char, LetterInfo> letters;

public:
    /**
     * @brief Constructor por defecto. Crea un letterSet vacío
     */
    LettersSet(); //Constructor por defecto

    /**
     * @brief Constructor de copia
     * @param other Objeto a copiar
     * @post El map se ve modificado si el map de other no es vacío
     */
    LettersSet(const LettersSet & other); // Constructor de copia

    /**
     * @brief Inserta un valor (pair) en el mapa
     * @param val Valor que se quiere insertar
     * @post El map se ve modificado si el valor a insertar no estaba ya en él
     * @return Un bool que indica si se ha realizado la inserción o no
     */
    bool insert(const pair<char,LetterInfo> & val);

    /**
     * @brief Elimina un carácter del map
     * @pre El map no puede estar vacío
     * @param key Carácter a eliminar
     * @post El map se ve modificado si tiene un elemento cuya clave es el valor dado a la función
     * @return Un bool que indica si se ha eliminado el carácter del map
     */
    bool erase(const char &key);

    /**
     * @brief Vacía el contenido del map
     * @post El map se ve modificado solo si no está vacío
     */
    void clear();

    /**
     * @brief Comprueba si el map está vacío
     * @return Un bool que indica si el map está vacío
     * @post El map no se ve modificado
     */
    bool empty() const;

    /**
     * @brief Indica el tamaño del map
     * @return El número de elementos del map
     * @post El map no se ve modificado
     */
    unsigned int Size() const;

    /**
     * @brief Calcula la puntuación de una palabra dada, como la suma de las puntuaciones de sus letras
     * @param word Palabra de la que queremos calcular la puntuación
     * @return La puntuación de la palabra
     * @post El map no se ve modificado
     */
    int getScore(string word) const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param cl map que se va a copiar
     * @return referencia al objeto actual
     * @post El map se ve modificado
     */
    LettersSet & operator=(const LettersSet &cl);

    /**
     * @brief Sobrecarga del operador de consulta. Accede a los elementos del map
     * @param val Carácter a consultar
     * @return El elemento del map que tiene como clave: val
     * @post El map no se ve modificado
     */
    LetterInfo & operator[](const char &val);

    /**
     * @brief Sobrecarga del operador de salida
     * @param os FLujo de salida donde se escribe el LetterSet
     * @param cl Datos (LetterSet que se escribe
     * @post El objeto no se ve modificado
     * @return Flujo de salida donde se han escrito los datos
     */
    friend ostream& operator<<(ostream &os, const LettersSet &cl);

    /**
     * @brief Sobrecarga del operador de entrada
     * @param is Flujo de entrada del que se leen los datos del LetterSet
     * @param cl Objeto LetterSet en el que se almacena la información leída
     * @post El objeto se ve modificado
     * @return Flujo de entrada
     */
    friend istream& operator>>(istream &is, LettersSet &cl);

    /**
     * @brief Iterador de la clase
     */
    class iterator{
    private:
        map<char, LetterInfo>::iterator it;
    public:
        iterator(){}
        iterator(const map<char, LetterInfo>::iterator& otro): it(otro){}
        iterator(const iterator& otro):it(otro.it){}
        ~iterator(){}
        iterator& operator=(const map<char, LetterInfo>::iterator& otro){
            it=otro;
            return *this;
        }
        iterator& operator=(const iterator& otro){
            it=otro.it;
            return *this;
        }
        pair<char, LetterInfo> operator*()const{
            return *it;
        }
        iterator& operator++(){
            ++it;
            return *this;
        }
        iterator& operator--(){
            --it;
            return *this;
        }
        iterator& operator++(int){
            it++;
            return *this;
        }
        iterator& operator--(int){
            it--;
            return *this;
        }
        bool operator!=(const iterator& otro){
            return it != otro.it;
        }
        bool operator==(const iterator& otro){
            return it == otro.it;
        }
    };

    /**
    * @brief Iterador constante de la clase
    */
    class const_iterator{
    private:
        map<char, LetterInfo>::const_iterator const_it;
    public:
        const_iterator(){}
        const_iterator(const map<char, LetterInfo>::const_iterator& otro): const_it(otro){}
        const_iterator(const const_iterator& otro):const_it(otro.const_it){}
        ~const_iterator(){}
        const_iterator& operator=(const map<char, LetterInfo>::const_iterator& otro){
            const_it = otro;
            return *this;
        }
        const_iterator& operator=(const const_iterator& otro){
            const_it = otro.const_it;
            return *this;
        }
        const pair<char, LetterInfo> operator*()const{
            return *const_it;
        }
        const_iterator& operator++(){
            ++const_it;
            return *this;
        }
        const_iterator& operator--(){--const_it;
            return *this;
        }
        const_iterator& operator++(int){
            const_it++;
            return *this;
        }
        const_iterator& operator--(int){
            const_it--;
            return *this;
        }
        bool operator!=(const const_iterator& otro){
            return const_it != otro.const_it;
        }
        bool operator==(const const_iterator& otro){
            return const_it == otro.const_it;

        }
    };

    iterator begin(){
        iterator i = letters.begin();
        return i;
    }
    iterator end(){
        iterator i = letters.end();
        return i;
    }
    const_iterator begin()const{
        const_iterator i = letters.begin();
        return i;
    }
    const_iterator end()const{
        const_iterator i = letters.end();
        return i;
    }
};

ostream& operator<<(ostream &os, const LettersSet &cl);
istream& operator>>(istream &is, LettersSet &cl);


#endif
