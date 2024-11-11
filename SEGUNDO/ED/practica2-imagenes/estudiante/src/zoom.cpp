//
// Created by lauralazaro on 16/10/21.
// Fichero: zoom.cpp
//Realiza un zoom 2X de una porción de una imagen mediante interpolación lineal
#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 6){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <fichero_origen> <fichero_resultado> <fila> <col> <filas_a_substraer> <cols_a_substraer>\n";
        exit (1);
    }

    int fila, col, lado;

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    fila= atoi(argv[3]);
    col=atoi(argv[4]);
    lado=atoi(argv[5]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    //Realizamos el zoom
    Image aux, zoom;
    aux = image.Crop(fila, col, lado, lado);
    zoom=aux.Zoom2X();

    // Guardar la imagen resultado en el fichero
    if (zoom.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}
