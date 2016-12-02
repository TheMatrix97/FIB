#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void usage(){
	char b[128];
	sprintf(b,"usage : arith n (n es un entero)(0 > n > 3) \n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}

void main(int argc, char *argv[]){
	if(argc < 2) usage();
	int num = atoi(argv[1]);
	if(num <= 0 || num >= 3) usage();
	int i = 0;
	int data;
	char buff[128];
	while(0 < read(0,&data,sizeof(int))){
		if(num == 1){
			int aux = data - 1;
			write(1,&aux,sizeof(int));
		}
		else{
			int aux = 1 << data;
			write(1,&aux,sizeof(int));
		}
}
}


