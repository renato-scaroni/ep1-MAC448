############################# Makefile ################################ 

CFLAGS=-Wall -ansi -pedantic -g

all: http_methods.o http_server

http_methods.o: src/http_methods.c src/http_methods.h
	gcc $(CFLAGS) -c src/http_methods.c -o http_methods.o

http_server: src/http_main.c http_methods.o
	gcc $(CFLAGS) http_methods.o src/http_main.c -o http_server

clean: 
	rm -rf *.o http_server

compacta: src/http_main.c src/http_methods.c src/http_methods.h
	tar -vzcf ep1-Andre-Renato.tar makefile src/