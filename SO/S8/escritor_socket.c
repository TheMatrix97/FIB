#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void main (int argc, char *argv[]){
	char buffer[64];
	int canal = open("pipe1",O_WRONLY); //abrir pipe modo escritura
	int ret = read(0,&buffer,sizeof(buffer));
	while(ret > 0){
		write(canal,buffer,ret);
		ret = read(0,&buffer,sizeof(buffer));
	}
}
