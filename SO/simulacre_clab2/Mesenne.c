#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage(){
	char b[128];
	sprintf(b,"usage : Mersenne (nombre archivo) \n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}
void tratar_errno(){
	char buff[60];
	sprintf(buff,"error numero: %i",errno);
	write(2,buff,strlen(buff));
	exit(EXIT_FAILURE);
}

void main(int argc, char *argv[]){
	if(argc != 2) usage();
	char* nombre = argv[1];
	int fd = open(nombre,O_RDONLY);
	if(fd == -1) tratar_errno();
	int p1[2],p2[2]; //declaramos pipes sin nombre 1 escritura 0 lectura
	pipe(p1);
	pipe(p2); //creamos las pipes
	int d = mknod("ff1",S_IFIFO|S_IRUSR|S_IWUSR,0);
	if(d == -1) {tratar_errno();}
	int ret1 = fork(); //creamos primer hijo
	if(ret1 == 0){ //arith1
		close(p1[1]);
		close(p1[0]);
		close(p2[0]); //cerramos canal de lectura
		close(1);
		dup(p2[1]); //redireccionamos pipe escritura estandar
		int fd_aux = open("./ff1",O_RDONLY);
		if(fd_aux < 0) tratar_errno();
		close(0);
		dup(fd_aux);
		execlp("./arith","arith","1",(char*) NULL);
		exit(1);
		
	}
	int ret2 = fork();
	if(ret2 == 0){ //arith2
		close(p1[1]); //cerramos canal escritura
		close(p2[1]);
		close(p2[0]);
		//printf("soy arith2 antes de hacer exec");
		close(0);
		dup(p1[0]); //redireccionamos pipe lectura estandar
		int fd_aux = open("./ff1",O_WRONLY);
		if(fd_aux < 0) tratar_errno();
		close(1);
		dup(fd_aux); //redireccionamos escritura a pipe nombre
		execlp("./arith","arith","2",(char*) NULL);
		perror("explode");
		exit(1);
	}
	close(p2[1]);
	close(p1[0]);
	int data,data2;
	int fd2;
	fd2 = open("salida",O_WRONLY|O_CREAT|O_EXCL,S_IRUSR|S_IWUSR);
	if(fd2 == -1 && errno == EEXIST){
		perror("el archivo salida ya existe %i\n");
		exit(1);
	}
	while(0 < read(fd,&data,sizeof(int))){
		write(p1[1],&data,sizeof(int));
		read(p2[0],&data2,sizeof(int));
		write(fd2,&data2,sizeof(int));
		char aux_b[120];
		sprintf(aux_b,"dato a guardar %i, enviado %i\n",data2,data);
		write(2,aux_b,strlen(aux_b));
			}
		}


