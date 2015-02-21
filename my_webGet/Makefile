PROGS =  createData webGet

all:    ${PROGS}

createData: createDataFiles.o createDataFiles
	gcc -ggdb -std=gnu99 -c createDataFiles.c

webGet: main.o utils.o core.o
	gcc -std=gnu99 -o webGet main.o utils.o core.o

clean:
	rm -rf *.o
	rm -rf createDataFiles 
	rm -rf webGet


backup:
	rm -f webGet.tar
	rm -f webGet.tar.gz
	tar -cf webGet.tar *
	gzip -f webGet.tar



main.o: main.c common.h globals.h
	gcc -std=gnu99 -c main.c

utils.o: utils.c common.h globals.h
	gcc -std=gnu99 -c utils.c

core.o: core.c common.h globals.h
	gcc -std=gnu99 -c core.c

