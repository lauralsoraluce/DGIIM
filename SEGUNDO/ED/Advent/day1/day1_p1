/**
 * @file day1_p1.cpp
 * @brief Advent of Code 2021: Day 1 Program 1
 * @author Laura Lázaro Soraluce
 * @date 2 december 2021
 */

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
