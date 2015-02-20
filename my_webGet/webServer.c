/*****************************************************************************************
*				Program: webServer														*
*				Description: A webGet server examples									*
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
#include <math.h>

unsigned long MAX_TRANSFER = 4294967296;

void usage();
void die(char *);

int main(int argc, char **argv){
	
	if(argc != 2) usage();
	int sock, connection;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	unsigned int clntAddrLen;
	unsigned short servPort;


	servPort = atoi(argv[1]);

	if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		die("Failed to open socket. Exiting.\n");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(servPort);

	if(bind(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		die("Failed to bind server \n");

	if(listen(sock, 1024) < 0)
		die("Failed to listen for connections\n");

	printf("webServer was bound on port %d\n", servPort);

	char *Buffer = malloc(sizeof(char) * 1024);
	for(;;){

		if((connection = accept(sock, (struct sockaddr *) &clntAddr, &clntAddrLen)) < 0)
			die("Error: failed on calling accept()\n");
		else {
			printf("Connected to client.. %d\n", clntAddrLen);
		}

		int byte_count;
		if((byte_count = recv(sock, &Buffer, sizeof(Buffer), 0)) < 0)
			printf("Error recieving from client\n");
	}


	close(sock);
	return 0;
}

void usage(){
	fprintf(stderr, "Error: usage is: ");
	printf("./webServer <port>\n");
	exit(-1);
}

void die(char *s){
	perror(s);
	exit(-1);
}