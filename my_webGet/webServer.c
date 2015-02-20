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
unsigned long bytesRecd = 0;
void usage();
void die(char *);
int safe_recv(int sock, char *buffer, int len);

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

	for(;;){
		char Buffer[1024];

		if((connection = accept(sock, (struct sockaddr *) &clntAddr, &clntAddrLen)) < 0)
			die("Error: Failed to connect to the client.\n");
	
		pid_t child;

		if((child = fork()) < 0)
			die("Error: Failed to fork()\n");
		else if(child == 0){
			if(recv(connection, &Buffer, 1024, 0) < 0)
				die("Error: Failed to recieve from the client.\n");
			else
				printf("Recieved from client\n");
		
			char *Data;
			Data = strtok(Buffer, "=");
			Data = strtok(NULL, " ");

			unsigned char outBuf[atoi(Data)];
			memset(outBuf, 0, atoi(Data));
			int i;
			for( i = 0; i < atoi(Data); ++i){
				printf("%c", outBuf[i]);
			}

			if(send(connection, outBuf, atoi(Data), 0) < 0)
				die("Error: Failed to send to the client.\n");

			close(connection);
			return 0;
		} else {
			int returnstatus;
			waitpid(child, &returnstatus, 0);

			if(returnstatus == 0){
				kill(child, SIGKILL);
			}
		}
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

int safe_recv(int sock, char *buffer, int len) {
  int recd;
  if ((recd = recv(sock, buffer, len, 0)) == -1) {
    die("recv() had a bad day");
  }
  printf("%s\n", buffer);
  buffer[recd] = '\0';
  bytesRecd += recd;
  return recd;
}