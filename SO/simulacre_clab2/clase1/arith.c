#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "dbg.h"
void usage(){
	char b[128];
	sprintf(b,"usage : arith n (n es un entero)(0 > n > 3) \n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}

void main(int argc, char *argv[]){
	if(argc != 2) usage();
	int num = atoi(argv[1]);
	if(num < 1 || num > 2) usage();
	int i = 0;
	int data;
	char buff[128];
	int ret,aux;
	while(ret=read(0,&data,sizeof(int)) > 0){
		if(num == 1){
			aux = data - 1;
		}
		else{
			 aux = 1 << data;
		}
		write(1,&aux,sizeof(int));
	}
	if(ret < 0) panic("fin de read");
}


