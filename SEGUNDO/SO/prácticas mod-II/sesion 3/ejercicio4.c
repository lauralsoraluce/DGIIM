#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t pid;
	pid_t waiting;
	int status;
	int number = 5;
	
	for (int i=0; i<number; i++) {
		pid=fork();
		if (pid ==-1) {
			fprintf(stderr, "Couldnt create child");
		}
		else if (pid == 0){
			printf("%s %d\n", "Soy el hijo", getpid());
			exit(-1);
		}
		else {
			waiting = wait(&status);
			printf("%s %d\n", "Acaba de finalizar mi hijo", waiting);
			printf("%s %d %s\n\n", "Solo me quedan", number-i-1, "hijos vivos");
		}
	}	
	
return 0;
}
