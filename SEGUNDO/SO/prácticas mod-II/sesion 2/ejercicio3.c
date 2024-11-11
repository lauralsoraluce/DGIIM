#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define S_IFXGRPOTH 011

#define comprobar(mode) ((((mode)& ~S_IFMT) & 011) == S_IFXGRPOTH)

void buscar(DIR *directories, int *count, char *pathname, int *size) {
	struct dirent *ed;
	struct stat atributos;
	DIR *directory;
	char cadena[500];
	directories = opendir(pathname);
	readdir(directories);
	ed=readdir(directories);
	
	while((ed=readdir(directories)) != NULL) {
		//if (strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0) {
                	sprintf(cadena, "%s/%s", pathname, ed->d_name);
	
			if(stat(cadena, &atributos)<0) {
				printf("Error al obtener los atributos");
				exit(-1);
			}
			if (S_ISDIR(atributos.st_mode)){
				if ((directory=opendir(cadena)) == NULL) {
					printf("Error al abrir el directorio actual");
				}
				else {
					buscar(directory, count, cadena, size);
				}
			}
			else {
				printf("%s %ld \n", cadena, atributos.st_ino);
			
				if (S_ISREG(atributos.st_mode)) {
					if (comprobar(atributos.st_mode)){
						*count++;
						*size += (int)atributos.st_size;
					}
				}
			}
		//}
	}
	
	closedir(directories);
}

int main(int argc, char *argv[]) {
	char pathname[500];
	DIR *directories;
	int count = 0;
	int size = 0;
	
	if (argc == 1) 
		strcpy(pathname, ".");
	else if (argc > 1)
		strcpy(pathname, argv[1]);
	else {
		printf("Error en el numero de argumentos.");
		exit(-1);
	}
	
	if((directories=opendir(pathname))==NULL){
		printf ("Error al abrir el direcrorio");
		exit(-1);
	}		
	
	printf("Los inodos son: \n\n");
	buscar(directories, &count, pathname, &size);
	printf("Hay %d archivos regulares con permiso x para grupo y otros\n", count);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", size);
	
	return 0;
}





