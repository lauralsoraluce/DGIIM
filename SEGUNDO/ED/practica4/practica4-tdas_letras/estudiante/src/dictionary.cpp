/**
 * @file dictionary.cpp
 * @brief  Archivo de implementación del TDA Dictionary
 * @author María Cribillés y Laura Lázaro
 */

#include "dictionary.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

Dictionary::Dictionary() {
    words.clear();
}

Dictionary:: Dictionary(const Dictionary & other){
    words=other.words;
}

bool Dictionary::exists(const string &val) const {
    set<string>::iterator it;
    it=words.find(val);
    return (it!=words.end());
}

bool Dictionary::insert(const string &val) {
    pair<set<string>::iterator,bool> ret;
    ret = words.insert(val);

    return ret.second;
}

bool Dictionary::erase(const string &val) {
    /*bool erased=false;
    if (!words.empty()) {
        words.erase(val);
        erased=true;
    }*/

    return words.erase(val);
}

void Dictionary::clear() {
    if (!words.empty())
        words.clear();
}

bool Dictionary::empty() const {
    return words.empty();
}

unsigned int Dictionary::size() const {
    return words.size();
}

int Dictionary::getOcurrences(const char c) const {
    set<string>::iterator it;
    int contador=0;
    for (it=words.begin(); it!=words.end(); ++it) {
        for (int i=0; i<it->length(); i++) {
            if (it->at(i)==c)
                contador++;
        }
    }
    return contador;
}

int Dictionary::getTotalLetters() const {
    set<string>::iterator it;
    int total=0;

    for (it=words.begin(); it!=words.end(); ++it){
        total+=it->length();
    }
    return total;
}

vector<string> Dictionary::wordsOfLength(int lenght) const {
    set<string>::iterator it;
    vector<string> elements;
    for (it=words.begin(); it!=words.end(); ++it){
        if(it->length()==lenght)
            elements.push_back(*it);
    }
    return elements;
}