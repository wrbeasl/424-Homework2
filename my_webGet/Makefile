PROGS =  createData webClient webServer

all:    ${PROGS}

createData: createDataFiles.o createDataFiles
	gcc -ggdb -std=gnu99 -c createDataFiles.c

webClient: main.o utils.o core.o
	gcc -std=gnu99 -o webClient main.o utils.o core.o

webServer:
	gcc webServer.c -o webServer

clean:
	rm -rf *.o
	rm -rf createDataFiles 
	rm -rf webClient
	rm -rf webServer

backup:
	rm -f HW2Q4.tar
	rm -f HW2Q4.tar.gz
	tar -cf HW2Q4.tar *
	gzip -f HW2Q4.tar



main.o: main.c common.h globals.h
	gcc -std=gnu99 -c main.c

utils.o: utils.c common.h globals.h
	gcc -std=gnu99 -c utils.c

core.o: core.c common.h globals.h
	gcc -std=gnu99 -c core.c


