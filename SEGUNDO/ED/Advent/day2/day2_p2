/**
 * @file day2_p2.cpp
 * @brief Advent of Code 2021: Day 2 Program 2
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
        int value=0, depth=0, horizontal=0, aim=0;
        is>>instruction;

        while (!is.eof()) {
            is>>value;

            if (instruction=="forward") {
                horizontal += value;
                depth+=(aim*value);
            }
            else if (instruction=="down")
                aim+=value;
            else if (instruction=="up")
                aim-=value;

            is>>instruction;
        }

        cout << depth*horizontal;
    }

    return 0;
}

