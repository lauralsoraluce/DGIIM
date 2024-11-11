#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int par(int number); 
int par(int number) {
	int answer = 0;
	if ((number%2) == 0)
		answer = 1;
	return answer;
} 

int main(int argc, char*argv[]) {
	if (argc!=2) {
		printf("Error en el numero de argumentos");
		exit(-1);
	}
	pid_t id_proceso;
	
	id_proceso=vfork();
	
	if (id_proceso == -1) {
		printf("Error con fork");
		exit(-1);
	}
	else if (id_proceso == 0) {
		int answer;
		answer = par(atoi(argv[1]));
		if (answer == 1)
			printf("El numero es par\n");
		else
			printf("El numero es impar\n");
		
	}
	else {
		wait(NULL);
		if ((atoi(argv[1])%4)==0)
			printf("El numero es divisible entre 4\n");
		else
			printf("El numero no es divisible entre 4\n");
	}

	return 0;
}
