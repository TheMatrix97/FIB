#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>



void main (int argc, char *argv[]){
	char buffer[64];
	int canal = open("pipe1",O_NONBLOCK | O_WRONLY); //abrir pipe modo escritura
	if(errno == ENXIO){
		char buffer_aux[64];
		sprintf(buffer_aux,"Esperando lector\n");
		write(1,buffer_aux,strlen(buffer_aux));
	}
	int ret = read(0,&buffer,sizeof(buffer));
	while(ret > 0){
		write(canal,buffer,ret);
		ret = read(0,&buffer,sizeof(buffer));
	}
}
