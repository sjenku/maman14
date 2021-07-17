myProg: main.o leacks_cheker_ex.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o errors.o
	gcc -Wall -ansi -pedantic -g main.o leacks_cheker_ex.o symbolList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o errors.o -o myProg
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
engineCompile.o: engineCompile.c headers/engineCompile.h headers/queue.h
	gcc -c -Wall -ansi -pedantic  engineCompile.c -o engineCompile.o
errors.o: errors.c headers/errors.h
	gcc -c -Wall -ansi -pedantic errors.c -o errors.o
leacks_cheker_ex.o: leacks_cheker_ex.c
	gcc -c -Wall -ansi -pedantic  leacks_cheker_ex.c -o leacks_cheker_ex.o
clean:
	rm *.o myProg
