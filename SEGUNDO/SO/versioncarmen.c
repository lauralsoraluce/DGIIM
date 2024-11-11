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

//#define mymask(mode) ((mode) & ~S_IFMT)
//#define S_IXUSR 100
//#define regla1(mode) ((((mode) & ~S_IFMT) & 100) == S_IXUSR)

int main(int argc, char* argv[]) {

    DIR* direct;
    direct = opendir (argv[2]);
    if(direct == NULL) {
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


    while((entity = readdir(direct)) != NULL) {

        if(stat(entity->d_name, &atrib_son) <0) {
            printf("No se pudo acceder a los atributos\n");
            exit(-1);
        }
        if(entity->d_type == DT_REG) {

            //printf("%s\n", cadena);
            if((atrib_son.st_mode & ~S_IFMT) &001){
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
