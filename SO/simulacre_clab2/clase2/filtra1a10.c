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
//	debug("file desc = %i",fd);
	char input;
	
	int a = 0;
	int i;
	int d = 0;
	int pos;
	for(i = 0; i <= 9; i++) write(fd,&d,sizeof(int));
	while((read(0,&input,sizeof(char))) > 0){ //llegim fins final d'entrada
		if(input >= '0' && input <= '9'){
			pos = input - '0';
	//		debug("pos = %i",pos);
			lseek(fd,pos*sizeof(int),SEEK_SET);
			read(fd,&a,sizeof(int));
		//	debug("he leido %i",a);
			a++;
		//	debug("voy a escribir %i en %i",a,pos);
			lseek(fd,pos*sizeof(int),SEEK_SET);
			write(fd,&a,sizeof(int));
		//	debug("he escrito %i",a);
			
		}
	}
	exit(0);
}
