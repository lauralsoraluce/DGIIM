//
// Created by lauralazaro on 16/10/21.
//

// Fichero: contraste.cpp
// Genera una imagen de niveles de gris con más contraste que la original
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
        cerr << "Uso: contraste <fichero_origen> <fichero_resultado> <e1> <e2> <s1> <s2>\n";
        exit (1);
    }

    int e1, e2, s1, s2;

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    e1= atoi(argv[3]);
    e2=atoi(argv[4]);
    s1=atoi(argv[5]);
    s2=atoi(argv[6]);

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

    //Subimos el contraste
    image.AdjustContrast(e1,e2,s1,s2);

    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}
