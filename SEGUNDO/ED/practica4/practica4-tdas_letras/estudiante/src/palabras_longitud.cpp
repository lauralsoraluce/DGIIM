#include "dictionary.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if(argc == 3) {
        ifstream is;
        is.open(argv[1]);

        Dictionary diccionario;
        string word;
        is >> word;
        while (!is.eof()) {
            if (!diccionario.exists(word))
                diccionario.insert(word);
            is >> word;
        }

        int longitud = atoi(argv[2]);

        vector<string> wordsFound;

        wordsFound=diccionario.wordsOfLength(longitud);

        cout << "Palabras de longitud " << longitud << endl;
        for (int i=0; i<wordsFound.size(); i++) {
            cout << wordsFound.at(i) << endl;
        }
    }
    return 0;
}