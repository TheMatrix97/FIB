
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
	int in,out,tamany;
	int suma_primo = 0;
	sprintf(buff,"%s-prime-map",argv[1]); //nombre fichero salida
	debug("abrimos: %s",argv[1]);
	if((in = open(argv[1], O_RDONLY)) < 0) panic("error open");
	debug("descriptor: %i",in);
	if((out = open(buff, O_WRONLY|O_CREAT|O_TRUNC,0664)) < 0) panic("error creacion fichero"); //se crea el fichero si no existe
    if((tamany = lseek(in,0,SEEK_END)) < 0) panic("lseek");
    debug("tamany = %i",tamany);
    int i,res;
    int num_procs = tamany / sizeof(int);
    for(i = 0; i < num_procs; i++){
		switch(fork()){
			case -1:
				panic("fork");
				break;
			case 0: //hijo
				if((in = open(argv[1], O_RDONLY)) < 0) panic("lseek");
				int data = lseek(in,-sizeof(int)*(i+1),SEEK_END);
				int aux;
				char aux2[60];
				if((read(in,&aux,sizeof(int))) < 0)panic("read");
				sprintf(aux2,"%i\n",aux);
				switch(fork()){
				case 0:
					execlp("./is_prime","./is_prime",aux2,NULL);
					panic("exclp");
				case -1:
					panic("segundo fork");
					break;
				default:
					wait(&res);
					if(WIFEXITED(res)){
						int data = WEXITSTATUS(res);
						if((out = open(buff, O_WRONLY)) < 0) panic("error");
						if((lseek(out,(num_procs-i-1)*sizeof(char),SEEK_SET)) < 0) panic("lseek");
						char pr;
						if(data){
							pr = 'p';
							//debug("el num: %i es primo",i);
						}
						else{
							pr = '-';
							//debug("el num: %i no es primo",i);
						}
						if((write(out,&pr,sizeof(char))) < 0) panic("error write");
					}else panic("no ha acabado normalmente");
					exit(WEXITSTATUS(res)); //finalizamos con el codigo
					break;
				}
			}	
	}
	int j,res_2;
	for(j = 0;j < num_procs;j++){
		waitpid(-1,&res_2,0);
		suma_primo += WEXITSTATUS(res_2);
	}
	if((out = open(buff, O_WRONLY)) < 0) panic("open");
	if((lseek(out,0,SEEK_END)) < 0) panic("lseek");
	char s = suma_primo +'0';
	debug("imprimire %c",s);
	if((write(out,&s,sizeof(char))) < 0) panic("write");
	exit(1);
}
	//debug("contador %i",i); 

