#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Info {int tillSolved; vector<vector<bool>> notSolved;};

Info Moves (string &input, vector<vector<int>> &matriz) {
    vector<int> numbers;
    vector<vector<bool>> found;
    string aux;
    bool bingo = false;
    int moves=0;

    for (int i=0; i<input.length(); i++) {
        if (input.at(i)!=',') {
            aux.push_back(input.at(i));
        }
        else {
            numbers.push_back(stoi(aux));
            aux.clear();
        }
    }

    for (int i=0; i<numbers.size() && !bingo; i++) {
        for (int j=0; j<5; j++) {
            for (int k=0; k<5; k++) {
                if (matriz[j][k] == numbers.at(i)) {
                    found[j][k]=true;
                }
            }
        }

        for (int l=0; l<5; l++) {
            bingo = true;
            for (int m=0; m<5 && bingo; m++) {
                if (!found[l][m]) {
                    bingo = false;
                }
            }
        }

        if (!bingo)
            moves++;
    }

    if (!bingo) {
        moves = -1;
    }
    Info returned {moves, found};

    return returned;
//
//    Info returned;
//    returned.tillSolved = moves;
//    returned.notSolved=found;
//    returned.original=matriz;
//    return returned;
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        ifstream is(argv[1]);
        string input = "";
        string number;
        int count=0;

        getline(is, input);

        vector<vector<vector<int>>> tablero;
        vector<int> aux1;
        vector<vector<int>> aux2;

        is >> number;

        int this_moves = 0;
        int least_moves = number.length();
        vector<vector<int>> least;

        while(!is.eof()) {
            for (int j=0; j<5; j++) {
                for (int i = 0; i < 5; i++) {
                    aux1.push_back(stoi(number));
                    is >> number;
                }
                aux2.push_back(aux1);
                aux1.clear();
            }
            tablero.push_back(aux2);

            this_moves = Moves(input, aux2).tillSolved;





            vector<int> numbers;
            vector<vector<bool>> found;
            string aux;
            bool bingo = false;
            int moves=0;

            for (int i=0; i<input.length(); i++) {
                if (input.at(i)!=',') {
                    aux.push_back(input.at(i));
                }
                else {
                    numbers.push_back(stoi(aux));
                    aux.clear();
                }
            }

            for (int i=0; i<numbers.size() && !bingo; i++) {
                for (int j=0; j<5; j++) {
                    for (int k=0; k<5; k++) {
                        if (matriz[j][k] == numbers.at(i)) {
                            found[j][k]=true;
                        }
                    }
                }

                for (int l=0; l<5; l++) {
                    bingo = true;
                    for (int m=0; m<5 && bingo; m++) {
                        if (!found[l][m]) {
                            bingo = false;
                        }
                    }
                }

                if (!bingo)
                    moves++;
            }

            if (!bingo) {
                moves = -1;
            }
            Info returned {moves, found};

            return returned;











            if (this_moves > -1 && this_moves < least_moves) {
                least_moves = this_moves;
                least = aux2;
            }
            aux2.clear();
        }

        vector<vector<bool>> found;
        found = Moves(input, least).notSolved;

        int sum=0;

        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if (found[i][j]==0){
                    sum+=least[i][j];
                }
            }
        }

        sum *= Moves(input, least).tillSolved;

        cout << sum;

    }

    return 0;
}
