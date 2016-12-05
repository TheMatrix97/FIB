#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "dbg.h"
int main(int arcg, char *argv[]){
	int fd;
	char buff[60];
	sprintf(buff,"ABCD");
	if((fd = creat("salida.txt",0600)) < 0) panic("creat");
	if((write(fd,buff,strlen(buff))) < 0) panic("write");
}
