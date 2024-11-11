/**
 * @file letters_bag.h
 * @brief TDA LettersBag
 * @details Almacena las letras disponibles y permite extraerlas
 * @author María Cribillés y Laura Lázaro
 */

#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__
#include "bag.h"
#include "letters_set.h"

using namespace std;
/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag {
private:
    Bag <char> letters;
public:
    /**
     * @brief Construtor por defecto. Crea un LettersBag() vacío
     */
    LettersBag();

    /**
     * @brief Constructor con argumentos. Dado un LettersSet, rellena la LettersBag con letras que contienen el
     * LettersSet, introduciendo cada letra el número de veces indicado.
     * @param lettersSet TDA LettersSet a parsear
     * @post El LetterSet no se ve modificado si el lettersSet es vacío
     */
    LettersBag(const LettersSet & lettersSet);

    /**
     * @brief Introduce una letra en la bolsa
     * @param I letra a añadir a la LettersBag
     * @post El LettersBag se ve modificado
     */
    void insertLetter(const char & I);

    /**
    * @brief Extrae una letra aleatoria de la bolsa, eliminándola del conjunto
    * @post El LettersBag se ve modificado
    * @return Devuelve un char que representa la letra extraída
    */
    char extractLetter();

    /**
     * @brief Extrae un conjunto de letras de la LettersBag, eliminándolas del conjunto
     * @param num Número de letras a extraer
     * @post El LettersBag se ve modificado
     * @return Lista con las letras extraídas aleatoriamente
     */
    vector<char> extractLetters(int num);

    /**
     * @brief Vacía la LettersBag
     * @post El LettersBag se ve modificado
     */
    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return int con el tamaño de la bolsa
     * @post El LettersBag no se ve modificado
     */
    unsigned int size() const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other LettersBag a copiar
     * @return Referencia a this, de esta forma el operador puede ser encadenado
     */
    LettersBag& operator=(const LettersBag& other);
};

#endif
