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

	
void main(int argc, char* argv[]){
	int fd = open("freq1a10.int",O_CREAT|O_TRUNC|O_RDWR,0660);
	int input;
	int a = 0;
	int i;
	int zero = 0;
	int pos;
	int r;
	for(i = 0; i <= 9; i++) write(fd,&zero,sizeof(zero)); //inicialitzem el fitxer
	while((r=read(0,&input,sizeof(input))) > 0){ //llegim fins final d'entrada
		if(r!=sizeof(input)) panic("partial read");
		if(input >= 0 && input <= 9){
			if(lseek(fd,input*sizeof(int),SEEK_SET) < 0) panic("lseek 1");
			if(read(fd,&a,sizeof(int)) < 0) panic("read");
			a++;
			if(lseek(fd,input*sizeof(int),SEEK_SET) < 0) panic("lseek 2");
			if(write(fd,&a,sizeof(int)) < 0) panic("write");
			
		}
	}
}
