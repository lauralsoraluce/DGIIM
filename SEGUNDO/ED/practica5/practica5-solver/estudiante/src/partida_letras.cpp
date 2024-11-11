

#include "solver.h"
#include "letters_bag.h"
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {
    srand(time(NULL));

    if (argc == 5) {

        // A partir de los argumentos dados, creamos el diccionario y el LettersSet para la partida

        ifstream is(argv[1]);
        LettersSet set;
        is >> set;
        is.close();

        ifstream is2(argv[2]);
        Dictionary dictionary;
        string word;

        while (is2) {
            is2 >> word;
            if (!dictionary.exists(word))
                dictionary.insert(word);
        }
        is2.close();

        // Creamos la bolsa de la que se irán sacando las letras a partir del lettersSet

        LettersBag bag(set);

        // Creamos el solver con el diccionario y el lettersSet anteriores

        Solver solver(dictionary, set);

        // Establecemos el modo de juego y sacamos un número n de letras aleatorias de la bolsa para jugar el turno

        string gameModeChar = argv[3];
        int num_letters = atoi(argv[4]);
        bool gameMode;
        if (gameModeChar == "L")
            gameMode = false;
        else if (gameModeChar == "P")
            gameMode = true;
        else
            cout << "ERROR: invalid game mode";

        vector<char> available_letters;

        available_letters=bag.extractLetters(num_letters);

        // Mostramos las letras disponibles para formar palabras en el turno

        cout << "LETRAS DISPONIBLES:" << endl;
        for (int i=0; i<available_letters.size(); i++) {
            cout << available_letters.at(i) << " ";
        }

        // Obtenemos las mejores palabras posibles en el turno y las mostramos

        pair<vector<string>,int> solution;
        solution = solver.getSolutions(available_letters, gameMode);

        cout << endl << "SOLUCIONES:" << endl;
        for (int i=0; i<solution.first.size(); i++) {
            cout << solution.first.at(i) << endl;
        }
        cout << "PUNTUACION:" << endl;
        cout << solution.second << endl;

    }
    return 0;
}

