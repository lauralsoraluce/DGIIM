#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char*argv[]) {
    ifstream is(argv[1]);

    int first, second;
    int counter = 0;

    is >> first;

    while (!is.eof()) {
        is >> second;

        if (second > first)
            counter++;

        first=second;
    }

    cout << counter;
}
