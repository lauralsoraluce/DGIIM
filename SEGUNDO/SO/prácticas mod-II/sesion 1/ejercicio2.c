#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
int fd, fileout;
if (argc==2) {
	if ((fd=open(argv[1], O_RDONLY))<0) {
		printf("\nError %d en open",errno);
 		perror("\nError en open");
 		exit(-1);
	}
}
else {
	fd = STDIN_FILENO;
}
if((fileout = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) < 0){
	printf("Error al abrir el archivo", errno);
      	perror("Error al abrir el archivo");
      	exit(-1);
}
	
char caracter[1];
int number = 1;
int cont = 1;
int leido;
char cad_bloque[40];

while ((leido = read(fd, caracter, 1)) != 0) {
	if (number == 1 || number % 80 ==0) {
		if (number !=1)
			write(fileout, "\n", strlen("\n"));
		else{
			sprintf(cad_bloque, "El numero de bloques es <%d>\n", cont);
			write(fileout, cad_bloque, strlen(cad_bloque));
		}
		sprintf(cad_bloque, "%s%d\n", "Bloque", cont);
		write(fileout, cad_bloque, strlen(cad_bloque));
		cont++;
	}
	write(fileout, caracter, 1);
	number++;
}

sprintf(cad_bloque, "El numero de bloques es <%d>\n", cont);
lseek(fileout, 0, SEEK_SET);	// Movemos puntero de escritura al inicio del archivo
write(fileout, cad_bloque, strlen(cad_bloque));

close(fd);
close(fileout);	
	
return 0;
}
