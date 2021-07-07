myProg: main.o
	gcc -ansi -g main.o -o myProg
main.o: main.c
	gcc -c -ansi  main.c -o main.o
