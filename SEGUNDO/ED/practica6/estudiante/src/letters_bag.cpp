/**
 * @file letter_set.cpp
 * @brief  Archivo de implementación del TDA LetterBag
 * @author María Cribillés y Laura Lázaro
 */

#include "letters_bag.h"

LettersBag::LettersBag() {}

LettersBag::LettersBag(const LettersSet &lettersSet) {
    LettersSet::const_iterator it;

    for (it = lettersSet.begin(); it != lettersSet.end(); ++it) {
        for (int i =0; i< (*it).second.repetitions; i++) {
            insertLetter((*it).first);
        }
    }
}

void LettersBag::insertLetter(const char &I) {
    letters.add(I);
}

char LettersBag::extractLetter() {
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num) {
    vector<char> elements;
    for (int i=0; i<num; i++)
        elements.push_back(extractLetter());

    return elements;
}

void LettersBag::clear() {
    letters.clear();
}

unsigned int LettersBag::size() const {
    return letters.size();
}

LettersBag & LettersBag::operator=(const LettersBag &other) {
    letters = other.letters;
    return *this;
}