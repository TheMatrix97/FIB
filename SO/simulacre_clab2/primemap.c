
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dbg.h"


void usage(){
	char b[128];
	sprintf(b,"usage : ./primemap (nombre archivo) \n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}
void main(int argc, char *argv[]){
	char buff[80];
	sprintf(buff,"%s-prime-map",argv[1]);
	//if(open(buff, O_WRONLY|O_CREAT,0664))
	//calcular mida del fitxer lseek lseek(fd,0,SEEK_END)
}
