#include <vector>
#include <string>
#include <iostream>

using namespace std;

void MatrizCalculos (string seq1, string seq2, vector<vector<int>> & matriz) {
	
	/*for (int i=0; i<=seq2.size(); i++) {
		matriz[i][0] = 0;
	}
	for (int j=0; j<=seq1.size(); j++) {
		matriz[0][j]=0;
	}*/
	
	for (int j=0; j<=seq2.size(); j++) {
		for (int i=0; i<=seq1.size(); i++) {
			if (j==0 || i==0) 
				matriz[i][j] = 0;
			else if (seq1[i-1] == seq2[j-1])
				matriz[j][i] = matriz[j-1][i-1]+1;
			else
				matriz[j][i]=max(matriz[j-1][i], matriz[j][i-1]);
		}
	}
		
}

string SubSecuencia1 (string seq1, string seq2, vector<vector<int>> & matriz) {
	
	string resultado = "";
	
	int indice1 = seq1.size();
	int indice2 = seq2.size();
	
	while (indice1 !=0 && indice2 !=0) {
		if (seq1[indice1-1]==seq2[indice2-1]) {
			resultado = seq2[indice2-1] + resultado;
			indice1--;
			indice2--;
		}
		else if (matriz[indice2][indice1]==matriz[indice2][indice1-1])
			indice1--;
		else
			indice2--;
	}
	
	return resultado;
		
}

string SubSecuencia2 (string seq1, string seq2, vector<vector<int>> & matriz) {
	
	string resultado = "";
	
	int indice1 = seq1.size();
	int indice2 = seq2.size();
	
	while (indice1 !=0 && indice2 !=0) {
		if (seq1[indice1-1]==seq2[indice2-1]) {
			resultado = seq2[indice2-1] + resultado;
			indice1--;
			indice2--;
		}
		else if (matriz[indice2][indice1]==matriz[indice2-1][indice1])
			indice2--;
		else
			indice1--;
	}
	
	return resultado;
		
}

int main() {
	
	string seq1 = "abbcdefabcdxzyccd";
	string seq2 = "abbcdeafbcdzxyccd";
	
	vector<vector<int>> matriz(seq2.size()+1, vector<int>(seq1.size()+1));	

	MatrizCalculos (seq1, seq2, matriz);
	
	string res1 = SubSecuencia1(seq1, seq2, matriz);
	string res2 = SubSecuencia2(seq1, seq2, matriz);
	
	for (int i=0; i<seq2.size()+1; i++) {
		for (int j=0; j<seq1.size()+1; j++) {
			cout << matriz[i][j] << "\t";
		}
		cout << endl;
	}
	
	int longitud = res1.length();
	double porcentaje = (1.0 * longitud / max(seq1.size(), seq2.size())) * 100;
	
	cout << "\nLa longitud de la subsecuencia más larga es: " << longitud << "\nSecuencia 1: " <<  res1 << "\nSecuencia 2: " << res2 << "\nEl porcentaje de parecido es: " << porcentaje << "%" << endl << endl;
	
	///////////////////////////////////////////////////////////////////////////
	
	seq1 = "010111000100010101010010001001001001";
	seq2 = "110000100100101010001010010011010100";
	
	vector<vector<int>> matriz2(seq2.size()+1, vector<int>(seq1.size()+1));	
	
	MatrizCalculos (seq1,seq2, matriz2);
	
	res1 = SubSecuencia1(seq1, seq2, matriz2);
	res2 = SubSecuencia2(seq1, seq2, matriz2);
	
	for (int i=0; i<seq2.size()+1; i++) {
		for (int j=0; j<seq1.size()+1; j++) {
			cout << matriz2[i][j] << "\t";
		}
		cout << endl;
	}
	
	longitud = res1.length();
	porcentaje = (1.0 * longitud / max(seq1.size(), seq2.size())) * 100;
	
	cout << "\nLa longitud de la subsecuencia más larga es: " << longitud << "\nSecuencia 1: " <<  res1 << "\nSecuencia 2: " << res2 << "\nEl porcentaje de parecido es: " << porcentaje << "%" << endl << endl;
	
	return 0;

}
