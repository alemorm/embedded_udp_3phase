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
#define PORT 5367
#define MAXLINE 1024 

int phasegenerator(float *phasevals, float *timechecked, float *randomnoise);

int main() { 
	int sockpifd, recvsig, n, clilen, servlen;
	int udpdelay = 1000.0/60.0;  //60 Hz frequency
	char clientaddress[40];
	float phasevals[3], randomnoise[3];
	float timechecked = 0;
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor 
	if ((sockpifd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	// Set the datagram memory value to 0
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Listening UDP server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_port = htons(PORT); 
	inet_aton(LOCAL_IP, &servaddr.sin_addr);
	
	// Bind the socket with the server address 
	if ( bind(sockpifd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	// Get size of datagrams
	clilen = sizeof(cliaddr); //len is value/resuslt 

	// Listen for signal from UDP gate
	n = recvfrom(sockpifd, (int *)&recvsig, sizeof(&recvsig), 
				0, ( struct sockaddr *) &cliaddr, 
				&clilen); 

	inet_ntop(AF_INET, &cliaddr.sin_addr, clientaddress, sizeof(clientaddress));

	// Print generator server information
	printf("Length = %d\n", n);
	printf("Received signal = %d\n", recvsig);
	printf("Server address = %s\n", clientaddress);
	printf("Server port = %d\n", htons(servaddr.sin_port));

	while(1) {
		// Generate the phase values
		phasegenerator(phasevals, &timechecked, randomnoise);

		// Send phase data to UDP gate
		sendto(sockpifd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &cliaddr, 
				clilen); 
		
		// Debug print
		// printf("Phase values : %f\t%f\t%f\n", phasevals[0], phasevals[1], phasevals[2]);
		
		// Pause the receiving/sending for 0.1 seconds
		usleep(udpdelay*1000);
	}
	
	return 0; 
} 

// Generate the simulated 3 phase power data
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
