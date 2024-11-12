#include <cstdlib>
#include <iostream>
#include <chrono>

#include <image.h>
#include <fstream>

using namespace std;

auto do_routine(int rows, int cols, int repeats) {
    // INICIO PARTE FUERA DEL CRONO
    Image image(rows,cols);

    // FIN FUERA DEL CRONO

    // start time
    auto start = chrono::high_resolution_clock::now();

    // INICIO PARTE DENTRO DEL CRONO
    for(int i=0; i<repeats;++i){
        image.ShuffleRows();
    }
    //FIN PARTE DENTRO DEL CRONO

    // end time
    auto stop = chrono::high_resolution_clock::now();
    // microseconds count
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    // return elapsed microseconds
    return duration;
}

int main (int argc, char ** argv) {

    int REPEATS = 100;
    ofstream f(argv[1]);

    f << "SIZE\t\tROWS\t\tCOLS\t\tELAPSED\n";
    for (int rows=100; rows<=2000; rows+=200){
        for (int cols=100; cols<=2000; cols+=200){
            f << rows*cols << "\t\t" << rows << "\t\t" << cols << "\t\t" << do_routine(rows,cols,REPEATS) << endl;
        }
    }
    return 0;
}