#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void main(){
	int valor;
	char buff[60];
	int ret = read(0,&valor,sizeof(int));
	sprintf(buff,"%i\n",valor);
	write(1,buff,strlen(buff));
	
}
