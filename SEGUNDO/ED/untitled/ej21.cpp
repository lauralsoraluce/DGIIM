//
// Created by lauralazaro on 27/11/21.
//
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Función que dice si una matriz (vector de vectores de enteros) es biordenada o no, es decir, si los elementos
 *          de cada una de sus filas y sus columnas están ordenados en orden no descendiente.
 * @param M Matriz que se va a comprobar
 * @post La matriz no se ve modificada
 * @return un bool diciendo que dice si es cierto que la matriz es biordenada o no
 */
bool esmatrizbiordenada (vector<vector<int>> &M) {
    bool correcto = true;

    int size = M.at(0).size();

    for (int i=0; i<size && correcto; i++) {
        for (int j=1; j<size && correcto; j++) {
            if (M.at(i).at(j)<M.at(i).at(j-1))
                correcto = false;
        }
    }

    for (int i=1; i<size && correcto; i++) {
        for (int j=0; j<size && correcto; j++) {
            if (M.at(i).at(j)<M.at(i-1).at(j))
                correcto=false;
        }
    }

    return correcto;
}

/**
 * @brief Función que añade las primeras columnas de una matriz (vector de vectores de enteros) al final de esta,
 *          dejando la columna indicada como la primera columna
 * @param col Columna que pasará a ser la primera
 * @param M Matriz sobre la que se realizará el cambio
 * @post La matriz se ve modificada siempre que col!=0
 */
void firstColumn (int col, vector<vector<int>> &M) {
    vector<vector<int>> aux;
    if (col>=0 && col<M.at(0).size()) {
        for (int i = col; i < M.at(0).size(); i++) {
            aux.push_back(M.at(i));
        }
        for (int i=0; i<col; i++) {
            aux.push_back(M.at(i));
        }

        M=aux;
    }
}

int main() {

    vector<vector<int>> matriz;
    int aux[] = {1,2,3,4,5,6};
    vector <int> aux1;

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            aux1.push_back(aux[j]);
        }
        matriz.push_back(aux1);
    }

    bool correcto=esmatrizbiordenada(matriz);

    cout << correcto << endl; // Debería ser 1

    //////////////////////////////////////////////

    vector<vector<int>> matriz2;
    int aux2[] = {1,2,3,7,5,6};
    vector<int>aux3;

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            aux3.push_back(aux2[j]);
        }
        matriz2.push_back(aux3);
    }

    correcto=esmatrizbiordenada(matriz2);

    cout << correcto << endl; // Debería ser 0.

    return 0;
}