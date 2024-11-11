/*
buscar.c
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

int main(int argc, char *argv[]) {
	
	char cadena[500]; // Para guardar el pathname completo de cada archivo que vamos abriendo
	struct stat atributos; // Para guardar los atributos de cada archivo que vamos leyendo
	struct dirent *dirinfo; // Para guardar la información de cada directorio o archivo que vamos leyendo
	DIR *directory; // Para guardar los archivos que hay dentro del directorio dado

	if (argc != 3) {
		printf("Error en el numero de argumentos");
		exit(-1);
	}

	/*Abrimos el directorio con el pathname dado como segundo argumento.*/
	directory = opendir(argv[2]);
	
	/* Si no se puede abrir el directorio dado, mostramos un mensaje de error. */
	if (directory == NULL) {
		printf("Error al abrir el directorio %s\n", argv[2]);
		exit(-1);
	}
	
	/* Leemos cada uno de los directorios y archivos que hay dentro del directorio dado como segundo argumento, es decir, el que acabamos de abrir, y cuyos directorios y archivos contenidos hemos guardado en dir. */
	while ((dirinfo = readdir(directory)) != NULL) {
		// Intentamos acceder a los atributos (información) del archivo que tenemos abierto
		if (stat(dirinfo->d_name, &atributos) <0) {
			printf("Error al acceder a los atributos\n");
			exit(-1);
		}
		
		// Comprobamos si se trata de un archivo regular
		if(S_ISREG(atributos.st_mode)) {
		
			//Comprobamos si el propietario (usuario) tiene permiso de ejecución
			if (atributos.st_mode == S_IXUSR) {
				
				/* Metemos pathname del archivo que estamos leyendo actualmente en cadena para poder mostrar su ruta completa. */
				strcpy(cadena, argv[1]);
				strcat(cadena, "/");
				strcat(cadena, dirinfo->d_name);
				strcat(cadena, &atributos);
				
				// Mostramos el archivo si cumple todos los requisitos
				if(strncmp(dirinfo->d_name, argv[1], strlen(argv[1]))==0)
					printf("El archivo %s cumple los requisitos", cadena);
			}
		}
		
	}
	
	return 0;
}

