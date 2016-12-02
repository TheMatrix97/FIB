all: arith Mesenne primemap

arith: arith.c dbg.h
	gcc -o arith arith.c
Mesenne: Mesenne.c dbg.h
	gcc -o Mesenne Mesenne.c
primemap: primemap.c dbg.h
	gcc -o primemap primemap.c
clean:
	rm *.o
	rm arith Mesenne primemap
