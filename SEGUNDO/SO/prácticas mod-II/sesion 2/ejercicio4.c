
/* Programa que recorre un sub-árbol con la función nftw */
/* Se basa en modificar el ejercicio anterior */

#define _XOPEN_SOURCE 500
/* 	Documentación del man:
	Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
       nftw(): _XOPEN_SOURCE >= 500
*/
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<libgen.h>
#include<ftw.h>

#define S_IFXGRPOTH 011

int buscar(const char* path, const struct stat *atributes, int flags, struct FTW* ftw);

#define comprobar(mode) ((((mode)& ~S_IFMT) & 011) == S_IFXGRPOTH)

int contador = 0;
int tam = 0;

int main(int argc, char *argv[]) {
	if(nftw(argc >= 2 ? argv[1] : ".", buscar, 10, 0) != 0) {
		perror("nftw");
	}
}

int buscar(const char* path, const struct stat *atributes, int flags, struct FTW* ftw) {
	for (int i=0; i<ftw->level; i++)
		printf("\t");
	if(flags==FTW_D){
		printf("El directorio %s\t%ld", path, atributes->st_ino);
		printf("que contiene:\n");
	}
	else if(flags==FTW_F)
		printf("%s\t%ld\n", path, atributes->st_ino);
	
	if ((atributes->st_mode & S_IXOTH) == S_IXOTH && (atributes->st_mode & S_IXGRP)==S_IXGRP) {
		contador++;
		tam+=atributes->st_size;
	}
	
	return 0;
}

