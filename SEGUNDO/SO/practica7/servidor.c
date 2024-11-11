#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define tamano 1024
#define longnombre 50


static void sig_hdlr(int sigNum) {

	//signal(SIGCHLD, sig_hdlr); // Para que se active por defecto 
	pid_t pid;
	pid = wait(NULL); 
	
} /* Signal handler. Cuando encuentre un pid, espera a que el hijo acabe. */

int main (int argc, char **argv) {
	if (argc!=2) {
		printf("Error en el numero de argumentos");
		exit(-1);
	} /* Tiene que haber un argumento, el nombre del FIFO que conecta el servidor y el cliente. */
	
	char nombre1[longnombre], nombre2[longnombre], nombreproxy[longnombre];
	/* Variables con los nombres de los FIFOS. */
	
	char buffer[tamano];
	/* Variable buffer que va a guardar la información, como paso intermedio al pasarla de un sitio a otro. */
	
	char *info_proxy; /* Variable que guarda el pid del proxy en formato char para que el servidor pueda informar al cliente de que proxy se va a hacer cargo de su petición. */
	
	int fde, fds, fd_proxy, info; /* Descriptores que corresponden al FIFO que conecta al cliente y al servidor (entrada y salida), y al cliente y al proxy. */
	
	pid_t pid_hijo, pid_proxy;
	
	sprintf(nombre1, "%se", argv[1]);
	sprintf(nombre2, "%ss", argv[1]);
	/* Componemos los nombres de los FIFO que conectan al servidor y al cliente en ambos sentidos. */
	
	unlink(nombre1);
	unlink(nombre2);
	/* Borramos todo lo que pudiese haber anteriormente asociado al nombre de los FIFOS. */
	
	umask(0);
	mkfifo(nombre1, 0777);
	mkfifo(nombre2, 0777);
	/* Le damos todos los permisos a todos. */
	
	if ((fde=open(nombre1, O_RDONLY))<0) {
		printf("Error %d en el open", errno);
		perror("Error en el primer open");
		exit(-1);
	}
	/* Abrimos el FIFO sólo para lectura, pues con este cogemos los datos que ha mandado el cliente. */
	
	if ((fds=open(nombre2, O_WRONLY))<0) {
		printf("Error %d en el open", errno);
		perror("Error en el segundo open");
		exit(-1);
	}
	/* Abrimos el FIFO sólo para escritura, pues con este vamos a decirle al cliente el pid del proxy que le va a atender. */
	
	info = read(nombre1, buffer, tamano);
	/* Leemos del primer FIFO la información que ha mandado el cliente. La guardamos en un buffer para poder comprobar errores antes de crear el proxy. */
	
	signal(SIGCHLD, sig_hdlr); /* Activamos el signal handler para que si hay un hijo que no ha terminado, le esperemos. */
	
	while (info > 0) { /* Mientras haya datos que coger del FIFO, los vamos cogiendo. */
		
		pid_hijo = fork(); /* Creamos un proceso hijo. */
		
		if (pid_hijo == 0) { /* Se está ejecutando el proceso hijo, es decir el proxy. */
			pid_proxy = getpid(); /* Cogemos el pid del proceso actual, que es el que se encarga de la petición del cliente. */
			
			sprintf(nombreproxy, "fifo.%d", pid_proxy); /* Componemos el nombre del FIFO que conceta el cliente y el proxy. */
			
			mkfifo(nombreproxy, 0777); /* Creamos dicho FIFO, dándole todos los permisos. */
			
			if ((fd_proxy = open(nombreproxy, O_RDONLY))<0) {
				printf ("Error %d en el open", errno);
				perror ("Error en el open del proxy");
				exit(-1);
			} /* Abrimos el FIFO, sólo para lectura, pues el proxy no escribe en él, sólo recoge información. */
			
			dup2(fd_proxy, STDIN_FILENO); /*Redirigimos la entrada. El FIFO proxy pasa a ser la entrada estándar del proxy. */
			
			execlp("./proxy", "proxy", NULL); /* Ejecutamos el proxy. */
			exit(0); 
		}
		if (pid_hijo>0) { /* Se está ejecutando el padre, es decir, el servidor. */
		
			sprintf (info_proxy, "%d", pid_proxy); /* Metemos el pid del proxy que creamos para encargarse de la petición del cliente y lo ponemos en formato char*. */
			
			if ((write(fds, info_proxy, sizeof(info_proxy)))<0) {
				printf("Error en el write");
				exit(-1);
			} /* Leemos el pid del proxy y lo mandamos por el FIFO que conecta con el cliente. */
		} 
		else if (pid_hijo<0) {
			printf("Error en el fork()");
			exit(-1);
		} /* Si hay algún error al crear el proceso, lo mostramos. */
		
		info = read(nombre1, buffer, tamano); /* Leemos el siguiente dato del FIFO de entrada al servidor. */
	}
	
	return 0;
}

