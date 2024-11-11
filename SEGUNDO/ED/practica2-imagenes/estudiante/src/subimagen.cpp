//
// Created by lauralazaro on 12/10/21.
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <fichero_origen> <fichero_resultado> <fila> <col> <filas_a_substraer> <cols_a_substraer>\n";
        exit (1);
    }

    int nrow, ncol, height, width;

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    nrow= atoi(argv[3]);
    ncol=atoi(argv[4]);
    height=atoi(argv[5]);
    width=atoi(argv[6]);

    // Mostramos argumentos
    //cout << endl;
    //cout << "Fichero origen: " << origen << endl;
    //cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    //Creamos la subimagen
    Image recorte;
    recorte=image.Crop(nrow, ncol, height, width);

    // Guardar la imagen resultado en el fichero
    if (recorte.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}

