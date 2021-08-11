assembler: main.o extCreator.o objectCreator.o engineCompile.o inputHandler.o symbolList.o dataSegment.o operetionSegment.o tools.o leacks_cheker_ex.o stringSeperator.o errors.o
	gcc -Wall -ansi -pedantic main.o extCreator.o objectCreator.o engineCompile.o inputHandler.o symbolList.o dataSegment.o operetionSegment.o tools.o leacks_cheker_ex.o stringSeperator.o errors.o -o assembler
main.o: main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o
extCreator.o:extCreator.c headers/extCreator.h
	gcc -c -Wall -ansi -pedantic extCreator.c -o extCreator.o
objectCreator.o:objectCreator.c headers/objectCreator.h
	gcc -c -Wall -ansi -pedantic objectCreator.c -o objectCreator.o
engineCompile.o:engineCompile.c headers/engineCompile.h
	gcc -c -Wall -ansi -pedantic engineCompile.c -o engineCompile.o
inputHandler.o:inputHandler.c headers/inputHandler.h
	gcc -c -Wall -ansi -pedantic inputHandler.c -o inputHandler.o
stringSeperator.o:stringSeperator.c headers/stringSeperator.h
	gcc -c -Wall -ansi -pedantic stringSeperator.c -o stringSeperator.o
tools.o: utils/tools.c headers/tools.h
	gcc -c -Wall -ansi -pedantic utils/tools.c -o tools.o
errors.o: errors.c headers/errors.h
	gcc -c -Wall -ansi -pedantic errors.c -o errors.o
operetionSegment.o:operetionSegment.c headers/operetionSegment.h
	gcc -c -Wall -ansi -pedantic operetionSegment.c -o operetionSegment.o
dataSegment.o:dataSegment.c headers/dataSegment.h
	gcc -c -Wall -ansi -pedantic dataSegment.c -o dataSegment.o
symbolList.o:symbolList.c headers/symbolList.h
	gcc -c -Wall -ansi -pedantic symbolList.c -o symbolList.o
leacks_cheker_ex.o: leacks_cheker_ex.c
	gcc -c leacks_cheker_ex.c -o leacks_cheker_ex.o

clean:
	rm *.o assembler
