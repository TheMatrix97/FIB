
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 8

int
esNumero (char *str)
{
  int i = 0;
  int contador = 0;
  int negativo = 0;
  int no_esnum = 0;
  if (str != NULL)
    {
      int size = strlen (str);
      while (i < size && no_esnum == 0)
	{
	  if (i == 0 && str[i] == '-')
	    negativo = 1;
	  else if (str[i] >= '0' && str[i] <= '9')
	    {
	      ++contador;
	      if (contador > 8)
		no_esnum = 1;
	    }
	  else
	    no_esnum = 1;
	  ++i;
	}
      if (no_esnum == 1)
	return 0;
      else
	return 1;
    }
  else
    return 0;
}

void
main (int argc, char *argv[])
{
  char buf[64];
  int res = esNumero (argv[1]);
  if (res == 1)
    {
      sprintf (buf, "es un num \n");
    }
  else
    sprintf (buf, "no es un num \n");
  write (1, buf, strlen (buf));
}
