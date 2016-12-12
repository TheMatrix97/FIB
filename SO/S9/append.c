#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "dbg.h"
int main(int arcg, char *argv[]){
	int fd;
	if((fd = open("file",O_RDWR)) < 0) panic("open");
	int tamany = lseek(fd,0,SEEK_END);
	debug("tamany : %i",tamany);
	int i;
	char aux;
	for(i = 0; i < tamany; i++){
		lseek(fd,i,SEEK_SET);
		read(fd,&aux,sizeof(char));
		debug("he leido %c",aux);
		lseek(fd,0,SEEK_END);
		write(fd,&aux,sizeof(char));
	
	}
}
