#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage(){
}
void inicializar(int fd){
	int i;
	int d = 0;
	for(i = 0; i <= 9; i++){
		write(fd,&d,sizeof(int));
	}
}
	
void main(int argc, char* argv[]){
	int fd = open("freq1a10.int",O_CREAT|O_TRUNC|O_RDWR,0660);
	char input;
	inicializar(fd);
	while((read(0,&input,sizeof(char))) > 0){ //llegim fins final d'entrada
		if(input >= '0' && input <= '9'){
			int pos = input - '0';
			lseek(fd,pos,SEEK_SET);
			int a;
			read(fd,&a,sizeof(int));
			a++;
			lseek(fd,pos,SEEK_SET);
			write(fd,&a,sizeof(int));
		}
	}	
}
