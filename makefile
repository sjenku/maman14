myProg: main.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o
	gcc -Wall -ansi -pedantic -g main.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o -o myProg
main.o: main.c headers/inputHandler.h headers/symbolList.h headers/asmbOperation.h headers/queue.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  main.c -o main.o
symbolList.o: symbolList.c headers/symbolList.h headers/tools.h
	gcc -c -Wall -ansi -pedantic symbolList.c  -o symbolList.o
tools.o: tools.c headers/tools.h
	gcc -c -Wall -ansi -pedantic  tools.c -o tools.o
inputHandler.o: inputHandler.c headers/inputHandler.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  inputHandler.c -o inputHandler.o
asmbOperation.o: asmbOperation.c headers/asmbOperation.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  asmbOperation.c -o asmbOperation.o
queue.o: queue.c headers/queue.h headers/tools.h
	gcc -c -Wall -ansi -pedantic queue.c -o queue.o
engineCompile.o: engineCompile.c headers/engineCompile.h
	gcc -c -Wall -ansi -pedantic  engineCompile.c -o engineCompile.o
clean:
	rm *.o myProg
