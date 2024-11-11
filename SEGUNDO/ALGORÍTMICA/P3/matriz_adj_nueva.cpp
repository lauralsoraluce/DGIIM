#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Punto2D {
private:
	double x;
	double y;
	
	void set_x(double coor_x){
		x=coor_x;
	}
	
	void set_y(double coor_y){
		y=coor_y;
	}
	
public:
	Punto2D() {
		x=-1;
		y=-1;
	}
	
	Punto2D(double coor_x, double coor_y) {
		x=coor_x;
		y=coor_y;
	}
	
	const double get_x() {
		return x;
	}
	
	const double get_y() {
		return y;
	}
	
	void set_both(double coor_x, double coor_y) {
		x=coor_x;
		y=coor_y;
	}
	
	double distancia (Punto2D uno) {
		return (sqrt(((uno.get_x()-this->get_x())*(uno.get_x()-this->get_x()))+((uno.get_y()-this->get_y())*(uno.get_y()-this->get_y()))));
	}
	
	bool es_igual(Punto2D otro) {
		return (this->get_x()==otro.get_x() && this->get_y()==otro.get_y());
	}
	
};




int VecinoMasCercano (int dim, int **matriz, vector<int> &recorrido) {
	
	//vector<int> recorrido; // Vector que contiene el recorrido 
	
	srand(time(0));
	int comienzo=rand()%dim; // Punto por el que comienza el recorrido
	recorrido.push_back(comienzo); 
	
	int insertar; // Siguiente punto a insertar en el recorrido
	bool cogido=false; // Indica si el punto que estamos analizando ya está en el recorrido
	int suma=0; // Suma total del recorrido
	
	while (recorrido.size()<dim) { // Mientras queden puntos por visitar
		int dist_min=10000000;
		
		for (int i=0; i<dim; i++) { // Comrpobamos todo los puntos
		
			cogido=false;
	
			for (auto j=recorrido.begin(); j!=recorrido.end() && !cogido; ++j){ //Comprobamos si el punto actual ya está en el recorrido
				if (i==(*j)) 
					cogido=true;
			}
			
			//Si no está cogido, nos quedamos con el punto que esté a menos distancia del último punto visitado
			if (!cogido && matriz[i][recorrido[recorrido.size()-1]]<dist_min) { 
				dist_min=matriz[i][recorrido[recorrido.size()-1]];
				insertar = i;
			}
		}

		// Insertamos el nuevo punto y añadimos la nueva distancia recorrida a la suma
		suma+=matriz[recorrido[recorrido.size()-1]][insertar];
		recorrido.push_back(insertar);
	}

	// Añadimos el primer punto visitado, para cerrar el ciclo
	suma+=matriz[recorrido[recorrido.size()-1]][comienzo];
	recorrido.push_back(comienzo);
	
	return suma;
};





void MatrizAdyacencia(int dim, int **matriz, Punto2D *puntos) {
	
	for (int i=0; i<dim; i++) {
		for (int j=0; j<dim; j++) {
			if (i!=j && matriz[i][j]==0) {
				matriz[i][j] = int(puntos[i].distancia(puntos[j]));
				matriz[j][i]=matriz[i][j];
			}
		}
	}
	
	for (int i=0; i<dim; i++) {
		for (int j=0; j<dim; j++) {
			cout << matriz[i][j] << "\t" << " ";
		}
		cout << endl;
	}
};



void TrianguloInicial (Punto2D *puntos, int dim, int &norte, int &oeste, int &este) {

	Punto2D p_norte;
	Punto2D p_oeste(1000000, -1);
	Punto2D p_este;
	oeste=0;
	este=0;
	norte=0;
	
	for (int i=0; i<dim; i++) { // Comprobamos todos los puntos
	
		if (puntos[i].get_x()<p_oeste.get_x()) { // Guardamos el que esté más al norte, oeste y este
			p_oeste=puntos[i];
			oeste=i;
		}
		if (puntos[i].get_x()>p_este.get_x()) {
			p_este=puntos[i];
			este=i;
		}
		if (puntos[i].get_y()>p_norte.get_y()) {
			p_norte=puntos[i];
			norte=i;
		}
	}
	
	int oeste_ant, este_ant;
	oeste_ant=oeste;
	este_ant=este;
	
	// Si el norte y el oeste coinciden, repetimos el procedimiento pero sin tener en cuenta el punto norte
	if(norte==oeste) { 
		p_oeste.set_both(10000,-1);
		for (int i=0; i<dim; i++) {
			if (i!=oeste_ant && puntos[i].get_x()<p_oeste.get_x()) {
				p_oeste=puntos[i];
				oeste=i;
			}
		}
	}
	
	// Si el norte y el este coinciden, repetimos el procedimiento pero sin tener en cuenta el punto norte
	if(norte==este) {
		p_este.set_both(-1,-1);
		for (int i=0; i<dim; i++) {
			if (i!=este_ant && puntos[i].get_x()>p_este.get_x()) {
				p_este=puntos[i];
				este=i;
			}
		}
	}
	
};

int Insercion(vector<int> &recorrido, int**matriz, int dim, int norte, int oeste, int este) {
// Metemos el triángulo inicial en el recorrido
	recorrido.push_back(norte);
	recorrido.push_back(oeste);
	recorrido.push_back(este);
	recorrido.push_back(norte);
	int suma=0;
	// Añadimos sus distancias a la suma 
	suma+=matriz[norte][oeste]+matriz[oeste][este]+matriz[este][norte];
	
	bool cogido=false; // Indica si el punto visitado ya está en el recorrido
	
	auto it_at=recorrido.begin(); // Iterador al 
	auto it_post = recorrido.begin();
	int copia1_suma; // Posible suma al insertar un nuevo nodo, aún no es definitiva


	for (int i=0; i<dim; i++) { // Comprobamos todos los puntos
		for (auto it=recorrido.begin(); it!=recorrido.end() && !cogido; ++it) {
			if (i==(*it))
				cogido = true;
		}
		if (!cogido) { // Si no está cogido el punto actual

			auto it=recorrido.begin(); // Iterador al segundo punto entre el que queremos insertar en el recorrido (para comprobar)
			auto anterior=it; // Iterador al primer punto entre el que queremos insertar en el recorrido (para comprobar)
			++it;
			auto min_it=it; // Iterador al punto donde finalmente vamos a insertar el nuevo punto (será el definitivo)

			// Guarda la menor suma total que hemos encontrado al calcular la inserción del punto actual entre todas las parejas de puntos que ya están en el recorrido
			int dist_min=suma - matriz[*it][*anterior] + matriz[i][(*it)]+matriz[i][(*anterior)]; 

			++it; 
			++anterior;
				
			for (it; it!=recorrido.end(); ++it) { // Comprobamos cuanto aumentaría la suma si insertásemos el punto actual entre cada una de las parejas
				copia1_suma=suma-matriz[*it][*anterior]+matriz[i][(*it)]+matriz[i][(*anterior)];
				if (copia1_suma <= dist_min) { // Si la suma total con la posibilidad de inserción actual es menor que todas las anteriores, esta pasa a ser la mínima
					dist_min = copia1_suma;
					min_it=it;
				}
				++anterior;
			}

			// Cuando ya hemos encontrado la mejor opción de inserción
			it_at=min_it;
			--it_at;
			it_post=min_it;
			++it_post;
			suma-=(matriz[*it_at][*min_it]); // Restamos la distancia entre los dos puntos entre los que vamos a insertar el nuevo punto

			recorrido.insert(min_it, i); // Lo insertamos
			
			suma+=(matriz[*min_it][*it_at] + matriz[*min_it][*it_post]); // Añadimos las dos nuevas distancias, de los dos puntos anteriores a este nuevo
		}
		cogido=false;
	}
	
	return suma;
};

vector<int> AlgoritmoPropio (int **matriz, int dim) {
	vector<int> minimo; // Guarda el recorrido mínimo según nuestro algoritmo
	srand(time(0));
	int comienzo=rand()%dim; // Punto por el que comienza el recorrido
	minimo.push_back(comienzo); // Añadimos el nodo por el que vamos a empezar 
	minimo.push_back(comienzo); // Lo añadimos de nuevo porque es también el del final 

	int dist_min=10000; // Distancia mínima encontrada, nos indicará que punto insertar
	int valor=0;
	int min1;
	bool cogido=false;
	auto iterador=minimo.begin();
	auto menos=minimo.begin();
	auto mas=minimo.begin();
	
	while (minimo.size()<=dim) { // Mientras no se hayan recorrido todos los puntos

		int dist_min=10000;
	
		for (auto it2=minimo.begin(); it2!=minimo.end(); ++it2) { // Para cada punto que ya pertenece al recorrido

			valor = *it2;
		
			for (int i=0; i<dim; i++) { // Comprobamos que otro punto que NO esté ya en el recorrido, es el más cercano al que estamos analizando
			
				for (auto it=minimo.begin(); it!=minimo.end() && !cogido; ++it) {
				
					if (i==(*it))
						cogido = true;
				}
		
				if (!cogido && matriz[i][valor]<dist_min) { 
					dist_min=matriz[i][valor]; // Vamos guardando la distancia mínima encontrada
					min1=i; // Vamos guardando el punto que más cerca está del actual, que podamos insertar
				
					iterador=it2; // Iterador que apunta al punto del recorrido que estamos analizando
					mas=++iterador; // Iterador que apunta al siguiente punto del recorrido al que estamos analizando (para insertar después del que estamos analizando)
					
					iterador=it2;
					
					if (iterador!=minimo.begin()) { // Si el punto que estamos analizando no es el primero del recorrido
						menos=--iterador; // Iterador que apunta al punto anterior del recorrido al que estamos analizando 

						if (matriz[min1][*menos]<matriz[min1][*mas]) // Si el punto que vamos a insertar está más cerca del punto anterior en el recorrido que del punto siguiente
							iterador=it2; // Lo insertamos con el iterador que apunta al elemento actual (se inserta delante del actual)
						else
							iterador=mas; // Lo insertamos con el iterador que apunta al elemento siguiente (se inserta después del actual)
					}
					else
						iterador=mas; // Si el punto que estmos analizando es el primero del recorrido, insertamos el nuevo punto después de él
					
				}
				cogido=false;
			}
			
			//valor=min1;
		}
		minimo.insert(iterador, min1); // Insertamos el nuevo punto
		//minimo.push_back(min1);
	}
	
	return minimo;
}


int main(int argc, char*argv[]) {


///////////////////////////////////////// MATRIZ ADYACENCIA /////////////////////////////////////////
	
	
	if (argc!=2) { 
		cout << "Error en el numero de argumentos" << endl; 
		exit(1); 
	};
	string nombre = argv[1];
	
	ifstream fich(nombre);
	if (!fich) {
		cout << "Error al abrir el fichero" << endl;
		exit(EXIT_FAILURE);
	}
	string aux1;
	int dim;
	double x,y;
	
	fich>>aux1>>dim;
	
	int **matriz = new int*[dim] ();
	
	//int matriz[dim][dim]={0};
	Punto2D nuevo;
	Punto2D *puntos = new Punto2D[dim];
	
	for(int i = 0; i < dim; ++i) {
		matriz[i] = new int[dim] ();
		puntos[i] = nuevo;
	}
	//Punto2D puntos[dim]={nuevo};
	
	for (int i=0; i<dim; i++) {
		fich>>aux1>>x>>y;
		nuevo.set_both(x,y);
		puntos[i]=nuevo;
	}
	
	MatrizAdyacencia(dim, matriz, puntos);
	
	
///////////////////////////////////////// VECINO MÁS CERCANO /////////////////////////////////////////
	
	
	clock_t tantes;    // Valor del reloj antes de la ejecución
	clock_t tdespues;  // Valor del reloj después de la ejecución
	double media=0;
	int suma=0;
	
	vector<int>recorrido;
	
	for (int i=0; i<15; i++) {
		recorrido.clear();
		tantes = clock();
		suma = VecinoMasCercano(dim, matriz, recorrido);
		tdespues = clock();
	
		media += (double)(tdespues-tantes)/CLOCKS_PER_SEC;
	}
	
	// MOSTRAR VECTOR 
		cout << endl << "Vecino mas cercano: " << endl;
		for (auto i=recorrido.begin(); i!=recorrido.end(); ++i) {
			cout << " " << (*i)+1 << " ";
		}
		cout << endl;
		
		cout << endl << "Suma total: " << suma << endl;
		
	cout << "La media de tiempo es: " << media << endl << endl;
	

///////////////////////////////////////// INSERCIÓN /////////////////////////////////////////

	
	int norte, oeste, este;
	
	for (int i=0; i<15; i++) {
		recorrido.clear();
		tantes=clock();
		TrianguloInicial(puntos, dim, norte, oeste, este);
		suma = Insercion(recorrido, matriz, dim, norte, oeste, este);
		tdespues=clock();
		media += (double)(tdespues-tantes)/CLOCKS_PER_SEC;
	}
	
	
	cout << "Norte:" << norte+1 << " Oeste:" << oeste+1 << " Este:" << este+1 << endl;
	
	

	// MOSTRAR VECTOR
	auto it=recorrido.begin();
	auto anterior=it;
	cout << "Inserción: " << endl << " " << (*it)+1 << " ";
	++it;
	
	for (it; it!=recorrido.end(); ++it) {
		cout << " " << (*it)+1 << " ";
	}
	cout << endl << endl << "Suma total: " << suma << endl;
	
	cout << "La media de tiempo es: " << media << endl << endl;


///////////////////////////////////////// ALGORITMO PROPIO /////////////////////////////////////////


	vector<int> minimo;
	
	for (int i=0; i<15; i++) {
		tantes=clock();
		minimo=AlgoritmoPropio(matriz, dim);
		tdespues=clock();
		media += (double)(tdespues-tantes)/CLOCKS_PER_SEC;
	}


	suma=0; // Ponemos la suma a 0

	it=minimo.begin(); 
	anterior=it;
	
	// MOSTRAR VECTOR

	cout << "Metodo propio: "<< endl << " " << (*it)+1 << " ";
	++it;

	for (it; it!=minimo.end(); ++it) {
		cout << " " << (*it)+1 << " ";
		tantes =clock();
		suma+=matriz[(*it)][(*anterior)];
		++anterior;
		tdespues=clock();
		media += (double)(tdespues-tantes)/CLOCKS_PER_SEC;
	}
	cout << endl << endl << "Suma total: " << suma << endl;
	
	cout << "La media de tiempo es: " << media << endl << endl;

}









