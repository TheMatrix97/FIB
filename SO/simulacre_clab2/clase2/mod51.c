#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void usage(){
	char buff[60];
	sprintf(buff, "usage: nom51 number\n");
	write(1,buff,strlen(buff));
	exit(0);
}

void main(int argc, char* argv[]){
	if(argc != 2) usage();
	int num = atoi(argv[1]);
	srand(getpid());
	int i,random,val;
	for(i=0;i<num; i++){
		random = rand();
		val = random % 51;
		if(write(1,&val,sizeof(val)) < 0) panic("write");
	}
}
