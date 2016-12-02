#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>


/* ESTA VARIABLE SE ACCEDE DESDE LA FUNCION DE ATENCION AL SIGNAL Y DESDE EL MAIN */
int segundos=0;
/* FUNCION DE ATENCION AL SIGNAL SIGALRM */
void funcion_alarma(int s)
{
char buff[256];
int time = alarm(10);
if(s == 14){
	segundos=segundos+ 10 - time;
	sprintf(buff, "ALARMA pid=%d: %d segundos\n",getpid(),segundos);
	write(1, buff, strlen(buff)); 
}
else{
	sprintf(buff,"Ha llegado un SIGURS1\n");
	write(1,buff,strlen(buff));
 }
	
}

int main (int argc,char * argv[])
{
	/* REPROGRAMAMOS EL SIGNAL SIGALRM */
	signal(SIGALRM,funcion_alarma);
	signal(SIGUSR1,funcion_alarma);
	alarm(10);
	while (segundos<100)
	{
		pause();
	}
	exit(1);
}
