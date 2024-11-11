class Sum {

private:

	int value;			// valor de la suma
	Punto2D * boxes;		// celdas en las que la suma está contenida
	
public:

	/**
	  * @brief Devuelve el valor de la suma
	  * @return El valor de la suma.
	  * @post El objeto no se ve modificado
	  */
	int getValue();

	/**
	  * @brief Accede a las celdas que contienen a la suma
	  * @param position la posición que se quiere consultar
	  * @return El punto position de la suma
	  * @post El objeto no se ve modificado
	  */
	Punto2D getBox(int position);
}



/******************************************************************************************************************************************************************************************************/



#include "suma.h"

class Sudoku {

private:

	int *** grid;      		// vectores en los que se almacena el tablero y las posibilidades de cada celda
	int nsums;			// número total de sumas
	const int ROWS = 9;	     	// número de filas del tablero
	const int COLS = 9;	     	// número de columnas del tablero
	int *** submatrix; 		// vector de submatrices contenidas en el tablero
	const int NUM_SUBMATRIX = 9	// número de submatrices
	const int ROWS_AUX = 3;	// número de filas de las submatrices
	const int COLS_AUX = 3;        // número de columnas de las submatrices
	Sum sums[nsums];		// objeto suma que contiene todas las sumas
	int count;			// llevará la cuenta de las celdas rellenadas
	
public:

	/**
      	  * @brief Constructor por defecto
      	  * @post Genera un tablero con 9x9, con nsums=0, count=0 y todas sus celdas a 0
      	  * @return El objeto sudoku creado.
          */
	Sudoku();

	/**
      	  * @brief Constructor con parámetros
      	  * @param sums Indica el número de sumas que hay en el tablero
      	  * @post Genera un tablero con 9x9, con nsums=sums, count=0 y todas sus celdas a 0
      	  * @return El objeto sudoku creado.
          */
	Sudoku (int sums);
	
	/**
      	  * @brief Verifica si existe una fila/columna/submatriz en la cual todas sus celdas vacías menos una, contengan una suma cerrada. En ese caso, calcula el valor de esa celda libre, que sería 			   igual a 45 (1+2+...+8+9) - la suma de las sumas de las demás celdas. Además, al rellenar una celda, comprueba cuántas celdas pertenecientes a esa suma quedan vacias, en el caso de 			   que solo quede una, la rellena
      	  * @post El objeto se ve modificado o no dependiendo de si se da el caso
          */
	void search();
	
	/**
      	  * @brief Comprueba que en una submatriz solo haya una suma abierta de tamaño n>2, en ese caso, si solo una celda vacía perteneciente a esa suma no se halla en la submatriz, entonces el 		   	   método calcula el valor de esa celda
      	  * @post El objeto se ve modificado o no dependiendo de si se da el caso
          */
	void solveSum();
	
	/**
      	  * @brief Método que guarda todas las posibilidades de cada celda
      	  * @post El objeto se ve modificado
          */
	void possibilities();
	
	/**
	  * @brief Método que va comprobando celda a celda si alguna de las posibilidades está en uso en alguna de su respectiva fila/columna/submatriz. Elimina aquellas posibilidades que ya están 			en uso y las posibilidades que combinadas con ellas dan el valor de la suma
	  * @post El objeto se modifica o no dependiendo de si se da el caso
	  */
	void deletePossibility();
	
	/**
	  * @brief Si existen n celdas de la misma fila/columna/submatriz con las mismas n posibilidades y ninguna más, entonces elimina esas posibilidades de las demás celdas de la fila / columna / 			submatriz
	  * @post El objeto se modifica o no dependiendo de si se da el caso
	  */
	void deletePossibilities();
	
	/**
	  * @brief Comprueba si alguna fila/columna/submatriz contiene una celda con una posibilidad distinta a las de las demás celdas de la fila/columna/submatriz. En ese caso, la rellena con ese 			valor
	  * @post El objeto se modifica o no dependiendo de si se da el caso
	  */
	void fill();
	
	/**
	  * @brief Mira si alguna fila/columna/submatriz tiene 8 celdas rellenas, en ese caso, calcula el valor de la celda restante
	  * @post El objeto se modifica o no dependiendo de si se da el caso
	  */
	void complete();
	
	/**
	  * @brief Rellena todo el tablero
	  * @post El Sudoku estará resuelto
	  */
	void solveSudoku();
	
	/*
		void sudoku::solveSudoku() {
		
			possibilities();
		
			do {
		
				search();
				solveSum();
				deletePossibility();
				deletePossibilities();
				fill();
				complete();
				
			
			} while (count < 81);
		}
	*/
}
