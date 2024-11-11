#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char *argv[])
{
	pid_t PID;
	DIR *dir;
	struct dirent *ed;
	struct stat atributos;
	char cadena[500];
	int estado;
	
	dir = opendir(argv[1]);
	
	while(((ed = readdir(dir)) != NULL)&&PID){
		strcpy(cadena,argv[1]);
		strcat(cadena,"/");
		strcat(cadena,ed->d_name);
		stat(cadena, &atributos);
		if(S_ISDIR(atributos.st_mode)){
			if(strcmp(".",ed->d_name) && strcmp("..",ed->d_name)){
				if((PID = fork())<0){
					perror("Error en el fork\n");
					exit(-1);
				}
				
				int size = 0;
				int numreg = 0;
					
				if(PID == 0){
					printf("Soy el hijo con PID %d y mi padre tiene PID %d\n",getpid(),getppid());
					DIR *subdir;
					subdir = opendir(cadena);
					char cadena1[500];
					struct stat atributos1;
					struct dirent *subed;
					while((subed = readdir(subdir)) != NULL){
						strcpy(cadena1,cadena);
						strcat(cadena1,"/");
						strcat(cadena1,subed->d_name);
						stat(cadena1, &atributos);
						if(S_ISREG(atributos.st_mode)){
							numreg++;
							size+=atributos.st_size;
						}
					}
					
					if(numreg >= 255) numreg = 255;
					printf("He recorrido el directorio %s\n",ed->d_name);
					printf("El tamaño total de los archivos regulares es %d bytes\n",size);
					printf("He encontrado %d archivos regulares\n",numreg);
				}
				else{
					PID = wait(&estado);
					printf("Mi hijo con PID %d ha finalizado\n",PID);
				}
			}
		}
	}
	return 0;
}
