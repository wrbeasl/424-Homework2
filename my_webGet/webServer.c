// webServer.c
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

#define CHUNKSIZE 10000

int iterations = 0;

void usage();
void die(char *);
void rec_iter_count(int sock, const struct sockaddr_in * clntAddr, int clntLen);

int main(int argc, char **argv){
	
	// Variables and arg check
	if(argc != 2) usage();
	int sock;
	unsigned long cur_req_size;
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

	int listenfd;

	if((listenfd = listen(sock, 1024)) < 0)
		die("Failed to listen for connections\n");

	printf("webServer was bound on port %d\n", servPort);

	rec_iter_count(sock, &clntAddr, clntAddrLen);

	for(;;){
		char DataSize[CHUNKSIZE];
		char returnHeader[10] = { "\r\n\r\n" };
		pid_t ChildProc;
		int connection;

		if((connection = accept(sock, (struct sockaddr *) &clntAddr, &clntAddrLen)) < 0){
			die("Error: Failed to accept client connections\n");
		}

		ChildProc = fork();

		if(ChildProc < 0){
			die("Failed to fork the child process, closing. \n");
		} else if (ChildProc == 0){
			printf("Child\n");

			if(recv(connection, DataSize, CHUNKSIZE, 0) < 0)
				die("Failed to recieve from the client\n");

			printf("%s\n", DataSize);
			char *req_size;
			req_size = strtok(DataSize, "=");
			req_size = strtok(NULL, " ");
			
			if(cur_req_size == 0 && atol(req_size) > CHUNKSIZE)
				cur_req_size = atol(req_size);

			if(atoi(req_size) > CHUNKSIZE){
				int size = atoi(req_size)/iterations;
				printf("%d", size);
				char Buffer[size];
				memset(Buffer, 1, size);
				int temp;
				temp = send(connection, returnHeader, 10, 0);
				if(temp < 0) die("Failed to send to client\n");

				temp = send(connection, Buffer, size, 0);
				if(temp < 0) die("Failed to send to client\n");

				cur_req_size -= size;
			} else {
				char Buffer[atoi(req_size)];
				memset(Buffer, 1, atoi(req_size));

				int temp;
				temp = send(connection, returnHeader, 10, 0);
				if(temp < 0) die("Failed to send to client\n");

				temp = send(connection, Buffer, atoi(req_size), 0);
				if(temp < 0) die("Failed to send buffer to client\n");

			}

			exit(0);
		} else {
			printf("Parent\n");
			int status;
			waitpid(ChildProc, &status, 0);

			if(status==0)
				kill(ChildProc, SIGTERM);

			printf("Killed child\n");
			close(connection);
		}
	}

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

void rec_iter_count(int sock, const struct sockaddr_in * clntAddr, int clntLen){
	int connection;
	if(( connection = accept(sock, (struct sockaddr *) &clntAddr, &clntLen)) < 0)
		die("Failed recieving iteration count\n");
	else
		printf("accepted\n");

	char Buff[10];

	if(recv(connection, &Buff, 10, 0) < 0)
		die("Failed to recieve iter count\n");

	iterations = atoi(Buff);
	printf("%d\n", iterations);
}
