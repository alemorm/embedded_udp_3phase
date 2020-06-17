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
#define RECV_PORT 20050
#define SEND_PORT 21050
#define MAXLINE 1024 

int main() { 
	int sockpifd, sockpcfd, n, clilen, servlen;
	float phasevals[3];
	int udpdelay = 100;
	int sendsigvar = 8;
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
	inet_aton(LOCAL_IP, &servaddr.sin_addr);

	// Client setup
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(SEND_PORT);
	inet_aton(REMOTE_IP, &cliaddr.sin_addr);

	clilen = sizeof(cliaddr); //len is value/resuslt 
	servlen = sizeof(servaddr); //len is value/resuslt 

	sendto(sockpifd, (const int *)&sendsigvar, sizeof(&sendsigvar), 
			0, (const struct sockaddr *) &servaddr, 
				servlen); 

	printf("Send signal = %d\n", sendsigvar);
	printf("Server address = %zu\n", servaddr.sin_addr.s_addr);
	printf("Server port = %u\n", servaddr.sin_port);

	while(1) {
		n = recvfrom(sockpifd, (float *)phasevals, sizeof(phasevals), 
				0, ( struct sockaddr *) &servaddr, 
				&servlen); 
		
		sendto(sockpcfd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &cliaddr, 
				clilen); 

		printf("Phase values : %f\t%f\t%f\n", phasevals[0], phasevals[1], phasevals[2]);
		usleep(udpdelay*1000);
	}
	
	return 0; 
} 
