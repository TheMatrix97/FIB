all: sin_nombre lector escritor escritor_v2

sin_nombre: sin_nombre.c
	gcc -o sin_nombre sin_nombre.c
lector: lector.c
	gcc -o lector lector.c
escritor: escritor.c
	gcc -o escritor escritor.c
escritor_v2: escritor_v2.c
	gcc -o escritor_v2 escritor_v2.c

clean:
	rm -r -f sin_nombre lector escritor escritor_v2
	rm *.o
