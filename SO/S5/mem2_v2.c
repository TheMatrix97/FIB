#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REGION_SIZE		4096

int *p;
void tratamiento(int s){
	char buff[64];
	
	sprintf(buff,"direccion de p: %p\n",&p);
	write(1,buff,strlen(buff));
	sprintf(buff,"valor variable que apunta p: \n");
	write(1,buff,strlen(buff));
	sprintf(buff,"el heap finaliza aqui: %p\n",p);
	write(1,buff,strlen(buff));
	exit(0);
	
	
}
int main(int argc, char *argv[])
{
	signal(SIGSEGV,tratamiento);
	int i = 0;
	char buff[256];					

	sprintf( buff, "Addresses:\n");
	write(1, buff, strlen(buff));	
	sprintf( buff, "\tp: %p\n", &p);
	write(1, buff, strlen(buff));	

	p = malloc(sizeof(int));
	
	if (p == NULL) {
		sprintf(buff, "ERROR en el malloc\n");
		write(2,buff,strlen(buff));
	}

	while (1) {
		*p = i;
		sprintf( buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
		      &p, p, *p);
		write(1, buff, strlen(buff));	
		p++;
		i++;
		p = malloc(sizeof(int));
	}

}
