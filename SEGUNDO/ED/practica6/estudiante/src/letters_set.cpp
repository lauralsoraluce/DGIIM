/**
 * @file letter_set.cpp
 * @brief  Archivo de implementación del TDA LetterSet
 * @author María Cribillés y Laura Lázaro
 */

#include "letters_set.h"

LettersSet::LettersSet() {
    letters.clear();
}

LettersSet::LettersSet(const LettersSet & other) {
    letters=other.letters;
}

bool LettersSet::insert(const pair<char,LetterInfo> &val) {
    pair<map<char,LetterInfo>::iterator,bool> ret;
    ret = letters.insert(val);

    return ret.second;
}

bool LettersSet::erase(const char &key) {
    /*bool erased = false;
    if (!letters.empty()) {
        letters.erase(key);
        erased = true;
    }*/
    return letters.erase(key);
}

void LettersSet::clear() {
    if (!letters.empty())
        letters.clear();
}

bool LettersSet::empty() const {
    return letters.empty();
}

unsigned int LettersSet::Size() const {
    return letters.size();
}

int LettersSet::getScore(string word) const {
    int suma=0;
    map<char,LetterInfo>::const_iterator it;
    bool done = false;

    for (int i=0; i<word.length(); i++) {
        for (it=letters.begin(); it!=letters.end() && !done; ++it) {
            if (toupper(word[i]) == it->first) {
                done = true;
                suma+=it->second.score;
            }
        }
        done=false;
    }

    return suma;
}

LettersSet &LettersSet::operator=(const LettersSet &cl) {
    letters=cl.letters;
    return *this;
}

LetterInfo &LettersSet::operator[](const char &val) {
    return letters[val];
}

ostream &operator<<(ostream &os, const LettersSet &cl) {
    os << "LETRA\tCANTIDAD\tPUNTOS";
    map<char,LetterInfo>::const_iterator it;
    for(it=cl.letters.begin(); it!=cl.letters.end(); ++it){
        os << it->first <<"\t" << it->second.repetitions << "\t" << it->second.score;
    }

}

istream &operator>>(istream &is, LettersSet &cl) {
    string random;
    char caracter;
    int score, reps;
    getline(is, random);
    do {
        is >> caracter >> reps >> score;
        pair<char,LetterInfo> insertar;
        LetterInfo nuevo;
        nuevo.score=score;
        nuevo.repetitions=reps;
        insertar.first=caracter;
        insertar.second=nuevo;
        cl.insert(insertar);
    } while(!is.eof());

}




