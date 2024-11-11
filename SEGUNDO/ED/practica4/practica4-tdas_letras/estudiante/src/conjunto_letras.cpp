#include "letters_set.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[]) {
    if (argc==3) {
        ifstream is;
        is.open(argv[1]);

        LettersSet set;

        is >> set;

        string word = argv[2];

        int puntuacion = set.getScore(word);

        cout << puntuacion << endl;
    }

    return 0;
}