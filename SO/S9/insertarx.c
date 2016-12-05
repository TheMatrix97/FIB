#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "dbg.h"
int main(int arcg, char *argv[]){
	int fd;
	char x = 'X';
	char ultimo;
	if((fd = open("salida.txt",O_RDWR)) < 0) panic("creat");
	if((lseek(fd,-sizeof(char),SEEK_END)) < 0) panic("lseek"); //tamany
	if((read(fd,&ultimo,sizeof(char))) < 0) panic("read");
	if((lseek(fd,-sizeof(char),SEEK_END)) < 0) panic("lseek"); //tamany
	if((write(fd,&x,sizeof(char))) < 0) panic("write");
	if((write(fd,&ultimo,sizeof(char))) < 0) panic("write");
}
