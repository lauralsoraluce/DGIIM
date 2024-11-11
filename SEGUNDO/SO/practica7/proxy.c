#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define tamano 1024

void block_unblock (int bloqueo, int type) {
	struct flock cerrojo;

	cerrojo.l_type= type; /* Ponemos el l_type en type, para poder usar la función tanto como para bloqueo de lectura, como de escritura, como para desbloqueo. */
	cerrojo.l_whence= SEEK_SET;
	cerrojo.l_start= 0;
	cerrojo.l_len = 0;

	if (fcntl(bloqueo, F_SETLKW, &cerrojo) < 0){
		printf("Error %d en el bloqueo", errno);
		perror("Error en el bloqueo");
		exit(-1);
	} /* Si hay algún error al bloquearlo lo mostramos. */
	
} /* Función para bloquear y desbloquear la pantalla al imprimir la información. */

int main(int argc, char **argv) {
	
	int info;
	char buffer[tamano]; /* Buffer para guardar los datos mientras los pasamos del FIFO al archivo temporal y viceversa. */
	
	FILE *temporal = tmpfile(); /* Archivo temporal. */
	
	info = read(STDIN_FILENO, buffer, tamano); /* Leemos la información que está en el FIFO del proxy. Recordamos que en el programa del servidor, redirigimos la entrada para que entrase por la estándar del proxy, por eso usamos STDIN_FILENO. Mandamos esta información al buffer, ya que no podemos pasarlo directamente al archivo temporal por si hay errores o es el final del archivo. */
	
	if (info<0) {
		printf("Error %d en el read", errno);
		perror("Error en el read");
		exit(-1);
	} /* Si hay algún error al leer la información del FIFO, lo mostramos. */
	
	while (info>0) {
		if ((fwrite(buffer, sizeof(buffer), info, temporal))<0) {
			perror("Error en el fwrite");
			exit(-1);
		}
	
		info = read(STDIN_FILENO, buffer, tamano);
		if (info<0) {
			perror("Error en el read");
			exit(-1);
		}
	} /* Mientras siga habiendo información en el FIFO para que el proxy la lea, seguimos leyéndola al buffer y escribiendola en archivo temporal. */
	
	int bloqueo; 
	
	block_unblock(bloqueo, F_WRLCK); /* Cuando hayamos acabado de leer la información que había en el FIFO y la hayamos escrito toda en el archivo temporal, bloqueamos la pantalla para poder mostrar en ella la información. */
	
	while (!feof(temporal)) {
		if (fread(buffer, sizeof(buffer), tamano, temporal)) {
			perror("Error en el fread");
			exit(-1);
		}
		
		if((write(STDOUT_FILENO, buffer, tamano))<0) {
			perror("Error en el write");
			exit(-1);
		}
	} /* Mientras no hayamos terminado de mostrar toda la información del archivo temporal, seguimos leyendo información y mostrándolos por la salida estándar. */
	
	block_unblock(bloqueo, F_UNLCK); /* Cuando hayamos terminado de mostrar toda la información que había, desbloqueamos la pantalla. */
	
	char *fifo_proxy;
	
	sprintf(fifo_proxy, "fifo.%d", getpid());
	unlink(fifo_proxy); /* Por último, el propio proxy se encarga de eliminar el FIFO creado por él mismo. */
	
	return 0;
}

