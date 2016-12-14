#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char* argv[]){
	int input;
	while((read(0,&input,sizeof(int))) > 0){ //llegim fins final d'entrada
		char a;
		a = '0' + input;
		write(1,&a,sizeof(char));
		}
	}	

