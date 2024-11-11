#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char*argv[]) {
    if (argc==2) {
        ifstream is(argv[1]);
        string number;
        vector <string> nums;

        is >> number;

        int ones[number.length()];
        int zeros[number.length()];

        for (int i=0; i<number.length(); i++) {
            ones[i]=0;
            zeros[i]=0;
        }

        for (int i=0; i<number.length(); i++) {
            if (number.at(i) == '1')
                ones[i]++;
            else
                zeros[i]++;
        }

        while(!is.eof()) {
            is >> number;
            for (int i=0; i<number.size(); i++) {
                if (number.at(i) == '1')
                    ones[i]++;
                else
                    zeros[i]++;
            }
        }

        int gamma, epsilon;

        for (int i=0; i<number.length(); i++) {
            if (ones[i]>zeros[i]){
                gamma+=(pow(2,number.length()-1-i));
            }
            else
                epsilon+=(pow(2,number.length()-1-i));
        }

        cout << "Gamma: " << gamma << endl;
        cout << "Epsilon: " << epsilon << endl;
        cout << "Total: " << gamma*epsilon << endl;

    }
}
