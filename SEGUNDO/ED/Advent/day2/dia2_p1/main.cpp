/**
 * @file day2_p1.cpp
 * @brief Advent of Code 2021: Day 2 Program 1
 * @author Laura Lázaro Soraluce
 * @date 2 december 2021
 */

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char*argv[]) {
    if (argc==2) {
        ifstream is(argv[1]);

        string instruction;
        int value=0, depth=0, horizontal=0;
        is>>instruction;

        while (!is.eof()) {
            is>>value;

            if (instruction=="forward")
                horizontal+=value;
            else if (instruction=="down")
                depth+=value;
            else if (instruction=="up")
                depth-=value;

            is>>instruction;
        }

        cout << depth*horizontal;
    }

    return 0;
}
