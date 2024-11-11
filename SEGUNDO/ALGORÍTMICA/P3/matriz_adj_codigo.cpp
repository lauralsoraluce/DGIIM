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
