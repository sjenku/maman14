myProg: main.o symbolList.o tools.o
	gcc -ansi -g main.o symbolList.o tools.o -o myProg
main.o: main.c symbolList.o
	gcc -c -ansi  main.c symbolList.o -o main.o
symbolList.o: symbolList.c tools.o symbolList.h tools.h
	gcc -c -ansi  symbolList.c tools.o -o symbolList.o
tools.o: tools.c tools.h
	gcc -c -ansi  tools.c -o tools.o
