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
#define PORT 20050
#define MAXLINE 1024 

int phasegenerator(float *phasevals, float *timechecked, float *randomnoise);

int main() { 
	int sockpifd, recvsigvar, n, clilen, servlen;
	int udpdelay = 100;
	int *recvsigptr = &recvsigvar;
	float phasevals[3], randomnoise[3];
	float timechecked = 0;
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor 
	if ((sockpifd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_port = htons(PORT); 
	// servaddr.sin_addr.s_addr = INADDR_ANY; 
	inet_aton(LOCAL_IP, &servaddr.sin_addr);
	
	// Bind the socket with the server address 
	if ( bind(sockpifd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	clilen = sizeof(cliaddr); //len is value/resuslt 

	n = recvfrom(sockpifd, (int *)recvsigptr, sizeof(recvsigptr), 
				0, ( struct sockaddr *) &cliaddr, 
				&clilen); 

	printf("Length = %d\n", n);
	printf("Received signal = %d\n", recvsigvar);
	printf("Server address = %zu\n", servaddr.sin_addr.s_addr);
	printf("Server family = %zu\n", inet_lnaof(servaddr.sin_addr));
	printf("Server port = %u\n", servaddr.sin_port);

	while(1) {
		// Generate the phase values
		phasegenerator(phasevals, &timechecked, randomnoise);

		sendto(sockpifd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &cliaddr, 
				clilen); 
		
		printf("Phase values : %f\t%f\t%f\n", phasevals[0], phasevals[1], phasevals[2]);
		
		// Delay for testing
		usleep(udpdelay*1000);
	}
	
	return 0; 
} 

int phasegenerator(float *phasevals, float *timechecked, float *randomnoise) {
	float amplitude = 120;
	float phaseoffset = (2.0*M_PI)/3.0;
	randomnoise[0] = (random() % 100)/1000.0;
	randomnoise[1] = (random() % 100)/1000.0;
	randomnoise[2] = (random() % 100)/1000.0;

	phasevals[0] = amplitude*(sin(*timechecked) + randomnoise[0]);
	phasevals[1] = amplitude*(sin(*timechecked + phaseoffset) + + randomnoise[1]);
	phasevals[2] = amplitude*(sin(*timechecked + 2*phaseoffset) + + randomnoise[2]);
	*timechecked += 0.1;
	return 0;
}
