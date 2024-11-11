#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>	
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/wait.h>
#include<string.h>


int main(int argc, char *argv[]) {
	if (argc!=2) {
		printf("Error con el numero de argumentos");
		exit(-1);
	}
	char cadena[500];
	char cadena1[500];
	int tam = 0, count = 0;
	
	pid_t current, parent, PID;
	current = getpid();
	parent = getppid();
	
	struct stat info;
	
	struct dirent *dirinfo;
	struct dirent *subdir;
	int estado;
	
	DIR *dir;
	
	if ((dir=opendir(argv[1])) == NULL) {
		printf("Error al abrir el directorio");
		exit(-1);
	}
	
	while ((dirinfo = readdir(dir))!=NULL) {
		if (strcmp(dirinfo->d_name, ".") != 0 && strcmp(dirinfo->d_name, "..") != 0) {
			pid_t hijo;
			count=0;
			tam=0;
			if ((hijo = fork())<0) {
				printf("Error al crear el proceso hijo");
				exit(-1);
			}
			else if (hijo == 0) {
				printf("PID hijo: %d\n", getpid());
				printf("PID padre: %d\n", getppid());
				strcpy(cadena, argv[1]);
				strcat(cadena, "/");
				strcat(cadena, dirinfo->d_name);
				strcat(cadena, &info);
				while ((subdir = readdir(cadena))!=NULL) {
					struct stat info1;
					strcpy(cadena1, cadena);
					strcat(cadena1, "/");
					strcat(cadena1, subdir->d_name);
					strcat(cadena1, &info1);
					if (S_ISREG(info1.st_mode)) {
						count++;
						tam += (info1.st_size);
					}
				}
				exit(-1);
			}
			else {
				PID = wait(&estado);
				printf("Mi hijo con PID %d ha terminado", PID);
				if (tam>255) tam=255;
				printf("El tamaño total de los archivos regulares es %d\n", tam);
				printf("Hay %d archivos regulares", count);
			}
		}
	}
	return 0;
}
