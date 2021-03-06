myProg: main.o leacks_cheker_ex.o dataGuidance.o labelList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o response.o engineChecker.o engineDB.o
	gcc -Wall -ansi -pedantic -g main.o leacks_cheker_ex.o dataGuidance.o labelList.o tools.o inputHandler.o asmbOperation.o queue.o engineCompile.o response.o engineChecker.o engineDB.o -o myProg

main.o: main.c headers/inputHandler.h headers/labelList.h headers/asmbOperation.h headers/queue.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  main.c -o main.o
labelList.o: data/labelList.c headers/labelList.h headers/tools.h
	gcc -c -Wall -ansi -pedantic data/labelList.c  -o labelList.o
tools.o: utils/tools.c headers/tools.h
	gcc -c -Wall -ansi -pedantic  utils/tools.c -o tools.o
inputHandler.o: engine/inputHandler.c headers/inputHandler.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  engine/inputHandler.c -o inputHandler.o
asmbOperation.o: data/asmbOperation.c headers/asmbOperation.h headers/tools.h
	gcc -c -Wall -ansi -pedantic  data/asmbOperation.c -o asmbOperation.o
queue.o: data/queue.c headers/queue.h headers/tools.h
	gcc -c -Wall -ansi -pedantic data/queue.c -o queue.o
engineCompile.o: engine/engineCompile.c headers/engineCompile.h headers/queue.h
	gcc -c -Wall -ansi -pedantic  engine/engineCompile.c -o engineCompile.o
response.o: data/response.c headers/response.h
	gcc -c -Wall -ansi -pedantic data/response.c -o response.o
engineChecker.o: engine/engineChecker.c headers/engineChecker.h
	gcc -c -Wall -ansi -pedantic engine/engineChecker.c -o engineChecker.o
engineDB.o : engine/engineDB.c headers/engineDB.h
	gcc -c -Wall -ansi -pedantic engine/engineDB.c -o engineDB.o
dataGuidance.o: data/dataGuidance.c headers/dataGuidance.h
	gcc -c -Wall -ansi -pedantic data/dataGuidance.c -o dataGuidance.o

leacks_cheker_ex.o: leacks_cheker_ex.c
	gcc -c leacks_cheker_ex.c -o leacks_cheker_ex.o

clean:
	rm *.o myProg
