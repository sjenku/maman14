myProg: main.o symbolList.o tools.o inputHandler.o
	gcc -ansi -g main.o symbolList.o tools.o inputHandler.o -o myProg
main.o: main.c inputHandler.h symbolList.h tools.h
	gcc -c -ansi  main.c -o main.o
symbolList.o: symbolList.c tools.o symbolList.h tools.h
	gcc -c -ansi  symbolList.c tools.o -o symbolList.o
tools.o: tools.c tools.h
	gcc -c -ansi  tools.c -o tools.o
inputHandler.o: inputHandler.c inputHandler.h
	gcc -c -ansi  inputHandler.c -o inputHandler.o

clean:
	rm *.o myProg
