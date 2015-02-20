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
void die(char *);
int findPort(char *);

double startTime, endTime, delay = 0.0;
int iterations, currIter, bytesSent, bytesRecd;
double avgThroughput = 0.0, avgResponseTime = 0.0;

int main(int argc, char **argv){

	if(argc != 5) usage();
	
	int sock, debug = 0;
	unsigned long DATASIZE;
	struct sockaddr_in svrAddr;
	char *domain = NULL;
	char *path = NULL;
	char *search = "DATASIZE=";
	int delim = findPort(argv[1]);
	unsigned short port;

	iterations = atoi(argv[2]);
	delay = atoi(argv[3]);

	if(iterations < 0 || delay < 0)
		die("Both 'iterations' and 'delay must be >= 0!\n");

	domain = malloc(sizeof(char) * delim + 1);
	int i = 0;
	for(i = 0; i < delim; ++i){
		domain[i] = argv[1][i];
	}

	printf("%s\n", domain);

	char *temp = malloc(sizeof(char) * 10);
	for(i = delim+1; argv[1][i] != '/'; ++i){
		temp[i] += argv[1][i];
	}

	// Doesn't actually contain the values
	printf("%s\n", temp);
	port = 5000;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("Failed to open socket\n");

	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_addr.s_addr = inet_addr(domain);
	svrAddr.sin_port = port;

	connect(sock, (struct *sockaddr) &svrAddr, sizeof(svrAddr));

	startTime = timestamp();

	sendto(sock, &DATASIZE, sizeof(DATASIZE), (struct sockaddr *) &svrAddr, sizeof(svrAddr));

  	for (currentIter = 0; (iterations <= 0) || (currentIter < iterations);) {
    /* Run the thing */
    iteration(&serverAddress, domain, DATASIZE, debugFlag);
    ++currentIter;  /* For more sane-looking dumps on ^C */
    
    /* Delay between iterations */
    usleep(delay * 1000000);
  }


	free(domain);
	//free(temp);
	close(sock);
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
void die(char *s){
	perror(s);
	exit(-1);
}