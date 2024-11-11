#include "cstdlib"
#include "ctime"
#include <iostream>
#include <string>
#include "letters_bag.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc==2) {
        LettersSet set;

        ifstream is;
        is.open(argv[1]);
        is >> set;

        LettersBag bag(set);

        vector<char> output;

        output = bag.extractLetters(bag.size());

        for (int i = 0; i < output.size(); i++) {
            cout << output.at(i) << endl;
        }
    }

    return 0;
}