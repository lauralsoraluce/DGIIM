#include "dictionary.h"
#include <fstream>
#include <iostream>
#include "letters_set.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        ifstream is(argv[1]);
        ifstream is2(argv[2]);

        Dictionary diccionario;
        string word;
        is >> word;
        while (is) {
            if (!diccionario.exists(word))
                diccionario.insert(word);
            is >> word;
        }

        LettersSet set;
        is2 >> set;
        double apariciones[set.Size()];
        int totalletras=0;
        double frec_rel[set.Size()];
        int totaldiccionario = diccionario.getTotalLetters();

        cout << "Letra\t" << "FAbs.\t" << "Frel." << endl;

        for (char j='A'; j<='Z' && ((j-'A')<set.Size()); j++) {
            if (set[j].repetitions>0) {
                apariciones[totalletras] = diccionario.getOcurrences(tolower(j));
                frec_rel[totalletras] = apariciones[totalletras]/totaldiccionario;
                cout << j << "\t" << apariciones[totalletras] << "\t" << frec_rel[totalletras] << endl;
                totalletras++;
            }
        }
    }

    return 0;
}