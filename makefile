all: update sources/grafo.o sources/grafo.h sources/lista.o sources/lista.h main.o
	@gcc sources/grafo.o sources/lista.o main.o -o exec
update:
	@rm -f sources/grafo.o sources/lista.o main.o exec
grafo.o:
	@gcc -c sources/grafo.c
lista.o:
	@gcc -c sources/lista.c
main.o:
	@gcc -c main.c
debug:
	@gcc sources/lista.c sources/grafo.c main.c -g
leak:
	@clear && gcc sources/lista.c sources/grafo.c main.c -o exec && valgrind --leak-check=yes ./exec
run:
	@./exec