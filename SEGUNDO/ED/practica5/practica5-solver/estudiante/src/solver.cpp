/**
 * @file solver.cpp
 * @brief  Archivo de implementación del TDA Solver
 * @author María Cribillés y Laura Lázaro
 */

#include "solver.h"

using namespace std;

Solver::Solver() {}

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {
    lettersSet = letters_set;
    this->dict = dict;
}

pair<vector<string>,int> Solver::getSolsLength(const vector<char> &available) {
    vector<string> words;
    vector<string> best_words; // Palabras más largas formadas con las letras dadas
    bool found = true;
    vector<char> copy;
    int length; // Longitud de las palabras válidas más largas encontradas
    int size = available.size();

    /*
     * Empezamos seleccionando las palabras más largas posibles. Si no se encontrase ninguna palabra de esta longitud
     * cuyas letras estuviesen entre las opciones disponibles, disminuimos en uno la longitud de las palabras que
     * buscamos y repetimos el proceso. Como vamos disminuyendo la longitud de las palabras que analizamos, en cuanto
     * encontremos una o varias palabras válidas (!best_words.empty()) sabemos que esas tienen la mayor longitud y
     * nos evitamos analizar palabras de longitudes inferiores.
     */
    for (int i=size; i>1 && best_words.empty(); i--) {
        words = dict.wordsOfLength(i);
        length = i;

        /*
         * Para cada palabra de la longitud que estamos analizando, comprobamos si todas sus letras están entre las
         * letras dadas para jugar el turno. Desde que una letra de una palabra del diccionario no se encuentre en el
         * conjunto de las letras dadas, descartamos la palabra y pasamos a analizar la siguiente.
         */
        for (int k = 0; k < words.size(); k++) {
            copy = available;
            for (int i = 0; i < words.at(k).size() && found; i++) {
                found = false;

                /*
                 * Utilizamos un vector copy para, al analizar cada palabra, cuando vayamos encontrando cada letra de
                 * la palabra en el conjunto dado, las vamos eliminando de copy, para saber cuales nos quedan
                 * disponibles. Cuando pasamos a analizar la siguiente palabra, reestablecemos copy (copy=available).
                 */
                for (int j = 0; j < copy.size() && !found; j++) {
                    if (words.at(k).at(i) == tolower(copy.at(j))) {
                        found = true;
                        copy.at(j) = copy.back();
                        copy.pop_back();
                    }
                }
            }

            /*
             * Si para una palabra, todas sus letras están entre las opciones disponibles, la añadimos al vector de
             * palabras válidas más largas.
             */
            if (found)
                best_words.push_back(words.at(k));
            found = true;
        }
    }

    // Devolvemos el vector de las palabras más largas, así como la longitud de estas.
    pair<vector<string>,int> sols;
    sols.second=length;
    sols.first=best_words;

    return sols;
}

pair<vector<string>,int> Solver::getSolsScore(const vector<char> &available) {
    vector<string> words; // Palabras con más puntuación formadas con las letras dadas
    int score = 0; // Puntuación de las palabras con más puntuación encontradas
    bool found = true;
    vector<char> copy;

    /*
     * Para cada palabra del diccionario, vamos comprobando si cada una de sus letras está entre las letras dadas para
     * jugar el turno, es decir, entre las letras a partir de las cuales podemos formar las palabras. Desde que una
     * letra de una palabra del diccionario no se encuentre en el conjunto de las letras dadas, descartamos la palabra
     * y pasamos a analizar la siguiente.
     */
    for (auto it = dict.begin(); it!=dict.end(); ++it) {
        copy = available;
        found = true;
        for(int i=0; i<(*it).size() && found; i++) {
            found = false;

            /*
             * Utilizamos un vector copy para, al analizar cada palabra, cuando vayamos encontrando cada letra de la
             * palabra en el conjunto dado, las vamos eliminando de copy, para saber cuales nos quedan disponibles.
             * Cuando pasamos a analizar la siguiente palabra, reestablecemos copy (copy=available).
             */
            for (int j=0; j<copy.size() && !found; j++) {
                if ((*it).at(i)==tolower(copy.at(j))) {
                    found = true;
                    copy.at(j)=copy.back();
                    copy.pop_back();
                }
            }
        }

        /*
         * Si para una palabra, todas sus letras están entre las opciones disponibles, comparamos su puntuación con la
         * puntuación de la mejor palabra que hayamos encontrado hasta el momento (score). Si la nueva palabra tiene
         * mejor puntuación, vaciamos el vector de las mejores palabras, y metemos la nueva. Actualizamos la mejor
         * puntuación. Si la nueva palabra tiene igual puntuación a la mejor, simplemente la añadimos al vector de
         * mejores palabras. Si tiene peor puntuación, la descartamos.
         */
        if (found) {
            if(lettersSet.getScore((*it))>=score){
                if (lettersSet.getScore((*it))>score) {
                    words.clear();
                    score = lettersSet.getScore((*it));
                }
                words.push_back((*it));
            }
        }
    }

    // Devolvemos el vector de mejores palabras, así como la puntuación de estas (la mejor puntuación encontrada).
    pair<vector<string>,int> sols;
    sols.second=score;
    sols.first=words;
    return sols;
}

pair<vector<string>,int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {
    pair<vector<string>,int> solutions;
    if (!score_game)
        solutions = getSolsLength(available_letters);
    else
        solutions = getSolsScore(available_letters);

    return solutions;
}