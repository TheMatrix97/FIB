#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void usage(){
}

void main(int argc, char* argv[]){
	if(argc != 2) usage();
	int num = atoi(argv[1]);
	srand(getpid());
	int i,random,val;
	for(i=0;i<num; i++){
		random = rand();
		val = random % 51;
		if((write(1,&val,sizeof(val))) < 0) panic("write");
	}
	exit(1);	
}
