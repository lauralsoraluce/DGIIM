/*
pares_impares.c
Laura Lázaro Soraluce
45350527R
20.12.2021
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "dirent.h"
#include "string.h"
#include "sys/wait.h"
#include "sys/stat.h"

int main(int argc, char*argv[]) {
	int fd1[2];
	int fd2[2];
	int valor, suma1, suma2;
	int i = 0;
	string cadena;
	char buffer[80];
	
	pipe(fd1);
	pipe(fd2);
	pid_t hijo1;
	pid_t hijo2;
	
	if (argc!=2) {
		printf("Error en el numero de argumentos");
		exit(-1);
	}
	
	if ((hijo1=fork())<0) {
		perror("Error en el fork");
		exit(-1);
	}
	if ((hijo2=fork())<0) {
		perror("Error en el fork");
		exit(-1);
	}
	
	// El hijo 1 se está ejecutando
	if (hijo1 == 0) {
		/* Mientras el valor que lea el hijo del cauce no sea -1, seguimos leyendo números y añadiendolos a la suma. */
		while ((valor = read(fd[0],buffer,sizeof(buffer)))!=(-1)) {
			suma1 += valor;
		}
		// Cuando se encuentre el -1, se escribe en el cauce el valor de la suma
		sprintf(cadena, "%d", suma1);
		write(fd1[1], cadena, strlen(cadena));
		// El hijo1 termina
		exit(-1);
	}
	// El hijo 1 se está ejecutando
	if (hijo2 == 0) {
		/* Mientras el valor que lea el hijo del cauce no sea -1, seguimos leyendo números y añadiendolos a la suma. */
		while ((valor = read(fd2[0]))!=(-1)) {
			suma2 += valor;
		}
		// Cuando se encuentre el -1, se escribe en el cauce el valor de la suma
		sprintf(cadena, "%d", suma2);
		write(fd2[1], cadena, strlen(cadena));
		// El hijo2 termina
		exit(-1);
	}
	
	//El padre se está ejecutando
	if(hijo2 != 0 && hijo1 != 0) {
		// Cerramos el descriptor de lectura de los cauces porque el padre sólo escribe en ellos.
		close(fd1[0]);
		close(fd2[0]); 
		
		for (i; i<argv[1]; i++) {
			// Si el número es par, lo metemos en el primer cauce
			if ((i%2) == 0) {
				sprintf(cadena, "%d", i);
				write(fd1[1], cadena, strlen(cadena));
			}
			// Si el número es impar, lo metemos en el segundo cauce
			else {
				sprintf(cadena, "%d", i);
				write(fd2[1], cadena, strlen(cadena));
			}
		}
		
		// Al terminar de meter todos los números en los cauces, metemos -1 en ambos
		sprintf(cadena, "%d", -1);
		write(fd1[1], cadena, strlen(cadena));
		write(fd2[1], cadena, strlen(cadena));
		
		// Cerramos los descriptores de escritura y abrimos los de lectura.
		close(fd1[1]);
		close(fd2[1]); 
		open(fd1[0]);
		open(fd2[0]);
		
		//Mostramos las sumas
		suma1=read(fd1[0],buffer,sizeof(buffer));
		printf("La suma 1 es %d\n", suma1);
		
		suma2=read(fd2[0],buffer,sizeof(buffer));
		printf("La suma 2 es %d\n", suma2);
	}
	
	return 0;
}
