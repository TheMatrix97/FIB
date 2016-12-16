#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void usage(){
	char buff[60];
	sprintf(buff,"usage: ./maxmin num1 num2....\n");
	write(1,buff,strlen(buff));
	exit(0);
}
void main(int argc, char* argv[]){
	int p[2];
	int nfills = argc-1;
	if(argc == 0) usage();
	int i;
	if(pipe(p) < 0) panic("pipe");
	for(i = 0; i < nfills; i++){
		switch(fork()){
			case -1:
				panic("fork");
				break;
			case 0:
				//codigo hijo escribira en la pipe, cerramos canal de lectura
				if(dup2(p[1],1) < 0) panic("dup2");
				if(close(p[0]) < 0) panic("close");
				if(close(p[1]) < 0) panic("close");
				//debug("ejecutamos mod51 %s",argv[i]);
				execlp("./mod51","mod51",argv[i+1],NULL);
				panic("exec");
				break;
		}
	}
	if(close(p[1]) < 0) panic("close");
	switch(fork()){//segundo hijo
		case -1:
			panic("fork2");
			break;
		case 0:
			if(dup2(p[0],0) < 0) panic("dup2");
			if(close(p[0]) < 0) panic("close");
			execlp("./filtra1a10","filtra1a10",NULL);
			panic("exec2");
			break;
	}
	while(waitpid(-1,NULL,0) > 0);
	int fd_freq;
	switch(fork()){
		case -1:
			panic("fork3"); //tercer hijo
			break;
		case 0:
			if((fd_freq = open("freq1a10.int",O_RDONLY)) < 0) panic("open");
			int data,max,imax,i;
			imax = 0;
			max = 0;
			i = 0;
			while(read(fd_freq,&data,sizeof(int)) > 0){
				if(max <= data){
					imax = i; 
					max = data;
				}
				i++;
			}
			char buff[160];
			sprintf(buff,"En freq1a10.int el valor más frecuente es el %i\n",imax);
			write(1,buff,strlen(buff));
			exit(0);
			break;
		default:
			if(waitpid(-1,NULL,0) < 0) panic("final waitpid");
	}
}
		


