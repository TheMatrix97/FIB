#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage(){
	char buff[60];
	sprintf(buff,"usage: ./maxmin num1 num2....");
	write(1,buff,strlen(buff));
}
void main(int argc, char* argv[]){
	int p[2];
	if(argc == 1) usage();
	int i;
	if(pipe(p) < 0) panic("pipe");
	for(i = 1; i < argc; i++){
		switch(fork()){
			case -1:
				panic("fork");
				break;
			case 0:
				//codigo hijo escribira en la pipe, cerramos canal de lectura
				close(p[0]);
				close(1);
				dup(p[1]);
				debug("ejecutamos mod51 %s",argv[i]);
				execlp("./mod51","./mod51",argv[i],NULL);
				panic("exec");
				break;
		}
	}
				//codigo padre
		switch(fork()){//segundo hijo
			case -1:
				panic("fork2");
				break;
			case 0:
				close(p[1]);
				close(0);
				dup(p[0]);
				execlp("./filtra1a10","./filtra1a10",NULL);
				panic("exec2");
				break;
			default:
				switch(fork()){
					case -1:
						panic("fork3"); //tercer hijo
						break;
					case 0:
						close(p[1]); //no usaremos las pipes
						close(p[0]);
						int fd_freq;
						if((fd_freq = open("freq1a10.int",O_RDONLY)) < 0) panic("open");
						int data,max,imax,i;
						max = 0;
						i = 0;
						while(read(fd_freq,&data,sizeof(int)) > 0){
							if(max < data) imax = i;
							i++;
						}
						char buff[160];
						sprintf(buff,"En freq1a10.int el valor más frecuente es el %i\n",i);
						write(1,buff,strlen(buff));
						exit(1);
						break;
					default:
						while((waitpid(-1,NULL,0)) > 0); //esperamos finalizaciond de todos ls hijos
						exit(1);
						break;
					}
					break;
				}
				exit(1);
			}
			
		
		
		
						

								
								
							
					
		
	


