/*****************************************************************************************
*				Program: webClient														*
*				Description: A webGet client example									*
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>     /* for memset() */
#include <netinet/in.h> /* for in_addr */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <netdb.h>      /* for getHostByName() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <unistd.h>     /* for close() */
#include <signal.h>

void usage();
int findPort(char *);

double startTime, endTime, delay = 0.0;
int iterations, currIter, bytesSent, bytesRecd;
double avgThroughput = 0.0, avgResponseTime = 0.0;

int main(int argc, char **argv){

	if(argc != 5) usage();
	
	int debug = 0;
	unsigned long DATASIZE;
	struct sockaddr_in svrAddr;
	char *domain = NULL;
	char *path = NULL;
	char *search = "DATASIZE=";
	int delim = findPort(argv[1]);

	domain = malloc(sizeof(char) * delim + 1);
	int i = 0;
	for(i = 0; i < delim; ++i){
		domain[i] = argv[1][i];
	}

	printf("%s\n", domain);
	
	return 0;
}

void usage(){
	fprintf(stderr, "Error: usage is: ");
	printf("./webClient http://darkhelmet.cs.clemson.edu:5000/DATASIZE=10000000 1 1 0\n");
	exit(-1);
}

int findPort(char *a){
	char *temp = malloc(sizeof(char) * sizeof(a) + 1);
	strcpy(temp, a);
	int i = 0, count = 0;
	for(i = 0; i < strlen(temp); ++i){
		if(temp[i] == ':' && count == 1)
			return i;
		else if (temp[i] == ':' && count == 0)
			count++;

	}

}