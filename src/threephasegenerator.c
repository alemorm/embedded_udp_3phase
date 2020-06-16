/* threephasegenerator.c */
#include <stdio.h> 
#include <math.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define LOCAL_IP "127.0.0.1"
#define REMOTE_IP "192.168.42.8"
#define RECV_PORT 21050
#define SEND_PORT 20050
#define MAXLINE 1024 

int phasegenerator(float *phasevals, float *timecheckedptr);

int main() { 
	int sockpifd, sockpcfd, n, clilen, servlen;
	float buffer[MAXLINE];
	float phasevals[3];
	float timechecked;
	float *timecheckedptr = &timechecked;
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor 
	if ((sockpifd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
		
	 // Create socket file descriptor
    if ((sockpcfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
    }

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_port = htons(RECV_PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	// servaddr.sin_addr.s_addr = inet_addr(LOCAL_IP);

	// Client setup
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(SEND_PORT);
    cliaddr.sin_addr.s_addr = inet_addr(REMOTE_IP);
	
	// Bind the socket with the server address 
	if ( bind(sockpifd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	clilen = sizeof(cliaddr); //len is value/resuslt 
	servlen = sizeof(servaddr); //len is value/resuslt 

	n = recvfrom(sockpifd, (float *)buffer, MAXLINE, 
				0, ( struct sockaddr *) &servaddr, 
				&servlen); 
	// buffer[n] = '\0'; 
	printf("Length %d\n", n);
	printf("Server address %zu\n", servaddr.sin_addr.s_addr);
	printf("Server family %zu\n", inet_lnaof(servaddr.sin_addr));
	printf("Server port %u\n", servaddr.sin_port);
	printf("Server address %s", servaddr.sin_zero);
	// printf("Client : %s\n", buffer);
	printf("Client : %f\t%f\t%f\n", buffer[0], buffer[1], buffer[2]);

	while(1) {
		// Generate the phase values
		phasegenerator(phasevals, timecheckedptr);

		sendto(sockpcfd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &cliaddr, 
				clilen); 
		// printf("Phase values sent.\n"); 
		sleep(0.1);
	}
	
	return 0; 
} 

int phasegenerator(float *phasevals, float *timecheckedptr) {
	float amplitude = 120;
	float phaseoffset = (2.0*M_PI)/3.0;
	
	phasevals[0] = amplitude*sin(*timecheckedptr);
	phasevals[1] = amplitude*sin(*timecheckedptr + phaseoffset);
	phasevals[2] = amplitude*sin(*timecheckedptr + 2*phaseoffset);
	*timecheckedptr += 0.1;
	return 0;
}
