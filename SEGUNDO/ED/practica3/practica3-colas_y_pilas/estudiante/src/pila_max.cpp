#include <iostream>
#include "maxstack.h"

using namespace std;

int main(int argc, char *argv[]){

    // Run the current exercise
    MaxStack stack;

    for(int i = 1; i < argc; i++){
        if (argv[i][0] == '.'){
            cout << stack.Top();
            stack.Pop();
        } else {
            stack.Push(atoi(argv[i]));
        }
    }
    return 0;
}
