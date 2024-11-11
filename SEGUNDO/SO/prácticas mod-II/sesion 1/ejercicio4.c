
#include <sys/stat.h>
#define S_ISREG2(mode) ((mode & S_IFMT) == S_IFREG)

int main (int argc, char*argv[]){
	struct stat ejemplo;
	
	if (argc!=2) {
		printf("Error");
		exit(-1);
	}
	else {
		if (lstat(argv[1], &atributes)<0) {
			printf("Error en lstat");
			exit(-1);
		}
		else {
			if (IS_REG2(atributes.st_mode)){
				printf("Es regular");
			}
			else
				printf("No es regular");
		}
	}
return 0;
}

