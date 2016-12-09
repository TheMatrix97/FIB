#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "dbg.h"
int main(int arcg, char *argv[]){
	int fd,fd2;
	char name2[60];
	char name[60];
	strcpy(name2,argv[1]);
	sprintf(name,".inv");
	strcat(name2,name);
	debug("%s",name2);
	if((fd = open(argv[1],O_RDONLY)) < 0) panic("open");
	if((fd2 = open(name2,O_CREAT|O_WRONLY|O_TRUNC,0600)) < 0) panic("open2");
	debug("lo he creado");
	int tamany = lseek(fd,0,SEEK_END);
	int i;
	lseek(fd,-1,SEEK_END);
	char aux;
	for(i=0; i < tamany; i++){
		read(fd,&aux,1);
		lseek(fd,-2,SEEK_CUR);
		write(fd2,&aux,1);
	}
}

