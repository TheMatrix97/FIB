#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>


void main (int argc, char *argv[]){
	char buffer[64];
	int ret;
	int pipe1[2]; //extremo 0 es lectura, el 1 es escritura
	pipe(pipe1);
	ret = fork();
	if(ret == 0){ //hijo
		close(0); //cerramos std input
		dup(pipe1[0]);
		close(pipe1[1]); //cerramos el canar de escritura 
		int aux = execlp("cat", "cat",(char *)NULL);
		if(aux == -1){
			sprintf(buffer,"Error execlp pid= %i", getpid());
			write(1,buffer,strlen(buffer));
		}
	}
	else{ //padre
		close(pipe1[0]); //cerramos el canal de lectura que usa el hijo
		sprintf(buffer,"Inicio\n");
		write(pipe1[1],buffer,strlen(buffer));
		//close(pipe1[1]);
		waitpid(-1,NULL,0);
		sprintf(buffer,"FIN\n");
		write(1,buffer,strlen(buffer));
	}
}
		
		
