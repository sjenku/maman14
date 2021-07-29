assembler: main.o tools.o leacks_cheker_ex.o stringSeperator.o
	gcc -Wall -ansi -pedantic main.o tools.o leacks_cheker_ex.o stringSeperator.o -o assembler
main.o: main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o
stringSeperator.o:stringSeperator.c headers/stringSeperator.h
	gcc -c -Wall -ansi -pedantic stringSeperator.c -o stringSeperator.o
tools.o: utils/tools.c headers/tools.h
	gcc -c -Wall -ansi -pedantic utils/tools.c -o tools.o

leacks_cheker_ex.o: leacks_cheker_ex.c
	gcc -c leacks_cheker_ex.c -o leacks_cheker_ex.o

clean:
	rm *.o assembler
