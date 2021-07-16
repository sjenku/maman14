myProg: main.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o
	gcc -ansi -g main.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o  -o myProg
main.o: main.c headers/inputHandler.h headers/symbolList.h headers/asmbOperation.h headers/queue.h
	gcc -c -ansi  main.c -o main.o
symbolList.o: symbolList.c headers/symbolList.h headers/tools.h
	gcc -c -ansi  symbolList.c  -o symbolList.o
tools.o: tools.c headers/tools.h
	gcc -c -ansi  tools.c -o tools.o
inputHandler.o: inputHandler.c headers/inputHandler.h headers/tools.h
	gcc -c -ansi  inputHandler.c -o inputHandler.o
asmbOperation.o: asmbOperation.c headers/asmbOperation.h headers/tools.h
	gcc -c -ansi  asmbOperation.c -o asmbOperation.o
queue.o: queue.c headers/queue.h headers/tools.h
	gcc -c -ansi queue.c -o queue.o

clean:
	rm *.o myProg
