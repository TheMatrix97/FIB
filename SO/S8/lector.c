#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void main (int argc, char *argv[]){
	char buffer[64];
	int canal = open("pipe1",O_RDONLY); //abrir pipe modo lectura
	int ret = read(canal,&buffer,sizeof(buffer));
	while(ret > 0){
		write(1,buffer,ret);
		ret = read(canal,&buffer,sizeof(buffer));
	}
}
