#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <queue>
#include "bit"
using namespace std;

int main(int argc, char*argv[]) {
    if (argc==2) {

        ifstream is(argv[1]);

        string number;
        vector<vector<char>> matriz;
        char value;
        int one, zero;
        vector<vector<char>> aux;
        vector<char> aux2;
        vector<vector<char>>matriz2;

        is>>number;

        while(!is.eof()) {
            for (int i=0; i<number.length(); i++) {
                aux2.push_back(number.at(i));
            }
            matriz.push_back(aux2);
            aux2.clear();
            is>>number;
        }

        matriz2=matriz;

        for (int j=0; j<number.length() && matriz.size()>1; j++) {
            for (int i = 0; i < matriz.size(); i++) {
                if (matriz[i][j] == '1')
                    one++;
                else
                    zero++;
            }

            if (one>=zero)
                value = '1';
            else
                value= '0';

            for (int i=0; i<matriz.size(); i++) {
                if (matriz[i][j]==value){
                    for (int k=0; k<number.size(); k++) {
                        aux2.push_back(matriz[i][k]);
                    }
                    aux.push_back(aux2);
                }
                aux2.clear();
            }

            matriz=aux;
            aux.clear();
            aux2.clear();
            one=zero=0;
        }

        for (int j=0; j<number.length() && matriz2.size()>1; j++) {
            for (int i = 0; i < matriz2.size(); i++) {
                if (matriz2[i][j] == '1')
                    one++;
                else
                    zero++;
            }

            if (one>=zero)
                value = '0';
            else
                value='1';

            for (int i=0; i<matriz2.size(); i++) {
                if (matriz2[i][j]==value){
                    for (int k=0; k<number.size(); k++) {
                        aux2.push_back(matriz2[i][k]);
                    }
                    aux.push_back(aux2);
                    aux2.clear();
                }
            }

            matriz2=aux;
            aux.clear();
            one=zero=0;
        }


        int oxygen=0, co2=0;

        for (int i=0; i<number.length(); i++) {
            int base = pow(2, number.length()-i-1);
            oxygen+=(matriz[0][i]-'0')*base;
            co2+=(matriz2[0][i]-'0')*base;

        }

        cout << "Oxygen: " << oxygen << endl;
        cout << "CO2: " << co2 << endl;
        cout << "Life Support Rating: " << oxygen*co2 << endl;


    }
}
