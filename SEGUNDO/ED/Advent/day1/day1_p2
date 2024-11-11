/**
 * @file day1_p2.cpp
 * @brief Advent of Code 2021: Day 1 Program 2
 * @author Laura Lázaro Soraluce
 * @date 2 december 2021
 */

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char*argv[]) {
    ifstream is(argv[1]);

    int first, second, third, fourth;
    int sum1, sum2;
    int counter = 0;

    is>>first>>second>>third;
    sum1=first+second+third;

    while (!is.eof()) {
        is >> fourth;
        sum2=second+third+fourth;
        if (sum2>sum1)
            counter++;
        first=second;
        second=third;
        third=fourth;
        sum1=sum2;
    }

    cout << counter;
}
