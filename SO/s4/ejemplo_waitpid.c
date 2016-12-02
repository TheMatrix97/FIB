#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
int hijosvivos[10];

void trata_alarma(int s) 
{

}
void trata_alarma2(int s) 
{
	int i;
	for(i = 0; i < 10; i++){
		if(hijosvivos[i] != -1){
			 kill(hijosvivos[i],SIGKILL);
			 hijosvivos[i] = -1;
		 }
	}
}

 void matar_hijo(int pid){
	 int i; 
	 for(i = 0; i < 10; ++i){
		 if(pid == hijosvivos[i]) hijosvivos[i] = -1;
	 }
 }
void print_vec(){
	int i;
	for(i = 0; i < 10; ++i){
		printf("pos %i, PID=%i\n",i,hijosvivos[i]);
	}
}

int main(int argc,char *argv[])
{
	int pid,res;
	char buff[256];		
	int contador = 0;
	int hijos=0;
	for (hijos=0;hijos<10;hijos++)
	{
		sprintf(buff, "Creando el hijo numero %d\n", hijos);
		write(1, buff, strlen(buff)); 
		
		pid=fork();
		if (pid==0) /* Esta linea la ejecutan tanto el padre como el hijo */
		{
			signal (SIGALRM, trata_alarma);
			/* Escribe aqui el codigo del proceso hijo */
			sprintf(buff,"Hola, soy %d\n",getpid());
			write(1, buff, strlen(buff)); 

			alarm(1); 
			pause();

			/* Termina su ejecución */
			exit(0);
		}else if (pid<0)	
		{
			/* Se ha producido un error */
			perror("Error en el fork");
		}
		else hijosvivos[hijos] = pid; //guardamos el pid del hijo en memoria del padre
	}
	int time;
	/* Esperamos que acaben los hijos */
	while (hijos > 0)
	{
		char buff2[60];
		signal (SIGALRM, trata_alarma2);
		alarm(2);
		pid=waitpid(-1,&res,0);
		time = alarm(0);
		matar_hijo(pid); //marcamos al hijo como muerto
		if(res == 0) sprintf(buff,"Termina el proceso ha hecho exit %d tiempo restante= %i\n",pid,time);
		else sprintf(buff,"Termina el proceso %d ha recibido un signal\n",pid);
		write(1, buff, strlen(buff)); 
		hijos --;
		contador++;
	}
	sprintf(buff,"Valor del contador %d\n", contador);
	write(1, buff, strlen(buff)); 
	return 0;
}
