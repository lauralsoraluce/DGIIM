/**
 * @file solver.h
 * @brief TDA Solver
 * @details Almacena el diccionario con las palabras y el letterset con la información de las letras para toda la
 *          partida. Trabaja con las palabras del diccionario utilizando métodos del LettersSet y de la LettersBag
 * @author María Cribillés y Laura Lázaro
 */

#include "dictionary.h"
#include "letters_set.h"
#include <set>
#include <iostream>

class Solver {
private:
    /**
     * @brief Diccionario que contiene las palabras válidas en la partida
     */
    Dictionary dict;

    /**
     * @brief LettersSet que contiene las letras válidas en la partida, así como su puntuación y sus repeticiones
     */
    LettersSet lettersSet;

    /**
     * @brief Obtiene las palabras con más puntuación formadas a partir de un conjunto de letras
     * @param available_letters Conjunto de letras a partir del que se pueden formar las palabras
     * @return Un pair con el vector que contiene las palabras con mayor puntuación formadas a partir de las letras
     *          dadas, y como segundo elemento, la puntuación de dichas palabras.
     * @post El objeto no se ve modificado
     */
    pair<vector<string>,int> getSolsLength(const vector<char> & available_letters);

    /**
     * @brief Obtiene las palabras más largas del diccionario formadas a partir de un conjunto de letras
     * @param available_letters Conjunto de letras a partir del que se pueden formar las palabras
     * @return Un pair con el vector que contiene las palabras más largas formadas a partir de las letras dadas, y
     *          como segundo elemento, la longitud de dichas palabras
     * @post El objeto no se ve modificado
     */
    pair<vector<string>,int> getSolsScore(const vector<char> & available_letters);

public:
    /**
     * @brief Constructor sin parámetros. Crea un objeto vacío.
     */
    Solver ();

    /**
     * @brief Constructor con parámetros que crea el objeto a partir de un diccionario y un set de letras.
     * @param dict Diccionario que contiene las palabras válidas en la partida
     * @param letters_set Set de letras que contiene las letras que hay en la partida, así como su información
     *          (repeticiones y puntuación).
     * @post El objeto se ve modificado si dict y letters_set no son vacíos.
     */
    Solver (const Dictionary & dict, const LettersSet & letters_set);

    /**
     * @brief Obtiene las mejores palabras que se pueden formar en el turno con las letras dadas
     * @param available_letters Conjunto de letras a partir del que se pueden formar las palabras
     * @param score_game Tipo de partida. Puede ser por longitud de palabra (false) o por puntuación de las letras
     *          (true)
     * @return Un pair con el vector que contiene a las mejores palabras formadas a partir de las letras dadas (las
     *          palabras más largas si es juego por longitud, y las que tengan mayor puntuación en el otro caso); y
     *          como segundo elemento la longitud de la palabra o su puntuación respectivamente
     * @post El objeto no se ve modificado
     */
    pair<vector<string>,int> getSolutions(const vector<char> & available_letters, bool score_game);
};