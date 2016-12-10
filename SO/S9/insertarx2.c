#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "dbg.h"
int main(int arcg, char *argv[]){
	int fd;
	char x = 'X';
	char contenido[60];
	int pos = atoi(argv[1]);
	if((fd = open("salida.txt",O_RDWR)) < 0) panic("creat");
	if((lseek(fd,pos,SEEK_SET)) < 0) panic("lseek"); //tamany
	int i = 0;
	while((read(fd,&contenido[i],sizeof(char))) > 0){
		i++;
	}
	debug("hay %i caracteres",i);
	if((lseek(fd,pos,SEEK_SET)) < 0) panic("lseek"); //tamany
	write(fd,&x,sizeof(char));
	int j;
	write(fd,&contenido,i);
}
		 
	
	


