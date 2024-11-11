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
#include "pwd.h"
#include "time.h"

int main(int argc, char* argv[]) {

    DIR* dir; // Para guardar los archivos que hay dentro del directorio dado
    
    /*Abrimos el directorio con el pathname dado como segundo argumento.*/
    dir = opendir (argv[2]);
    
    /* Si no se puede abrir el directorio dado, mostramos un mensaje de error. */
    if(dir == NULL) {
        printf("Error\n");
        exit(-1);
    }
    struct dirent* entity;
    struct stat atrib_son;

    //para obeter el path actual
    char cwd[1900];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

	

    /* Leemos cada uno de los directorios y archivos que hay dentro del directorio dado como segundo argumento, es decir, el que acabamos de abrir, y cuyos directorios y archivos contenidos hemos guardado en dir. */
    while((entity = readdir(dir)) != NULL) {

	// Intentamos acceder a los atributos (información) del archivo que tenemos abierto
        if(stat(entity->d_name, &atrib_son) <0) {
            printf("No se pudo acceder a los atributos\n");
            exit(-1);
        }
        
        // Comprobamos si se trata de un archivo regular
        if(entity->d_type == DT_REG) {

            //Comprobamos si el propietario (usuario) tiene permiso de ejecución
            if(atrib_son.st_mode == S_IXUSR){
                //printf("%s\n", entity->d_name);
                char*cadena = entity->d_name;
                if(strncmp(cadena, argv[1], strlen(argv[1])) == 0){
                    char cadena[3000];
                    sprintf(cadena, "%s/%s", cwd, entity->d_name);
                    printf("%s\n", cadena);
                }
            }
        }
    }


    return 0;
}
