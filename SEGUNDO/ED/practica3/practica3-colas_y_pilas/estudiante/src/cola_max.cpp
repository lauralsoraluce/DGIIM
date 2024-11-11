#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "maxqueue.h"

using namespace std;

int main(int argc, char *argv[]){

    // Run the current exercise
    MaxQueue queue;

    for(int i = 1; i < argc; i++){
        if (argv[i][0] == '.'){
            cout << queue.Front();
            queue.Pop();
        } else {
            queue.Push(atoi(argv[i]));
        }
    }
    return 0;
}
