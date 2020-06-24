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

int phasegenerator(float *phasevals, float *recvsig);

int main() { 
	int sockpifd, n, clilen, servlen;
	char clientaddress[40];
	float phasevals[4], recvsig[4];
	phasevals[3] = 0; //Initial time is 0
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
	clilen = sizeof(cliaddr);

	// Listen for signal from UDP gate
	n = recvfrom(sockpifd, (float *)recvsig, sizeof(recvsig), 
				0, ( struct sockaddr *) &cliaddr, 
				&clilen); 

	inet_ntop(AF_INET, &cliaddr.sin_addr, clientaddress, sizeof(clientaddress));

	if (recvsig[3] > 0) {
		// Print debug generator server information
		printf("Length = %d\n", n);
		printf("Received noise = %8.3f\n", recvsig[0]);
		printf("Received time step = %8.3f\n", recvsig[1]);
		printf("Received frequency = %8.3f\n", recvsig[2]);
		printf("Received debug = %8.3f\n", recvsig[3]);
		printf("Server address = %s\n", clientaddress);
		printf("Server port = %d\n", htons(servaddr.sin_port));
	}

	while(1) {
		// Generate the phase values
		phasegenerator(phasevals, recvsig);

		// Send phase data to UDP gate
		sendto(sockpifd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &cliaddr, 
				clilen); 
		
		if (recvsig[3] > 0) {
			// Debug print
			printf("Phase values : %8.3f | %8.3f | %8.3f | Time (s): %8.2f\n", phasevals[0], phasevals[1], phasevals[2], phasevals[3]);
		}
		
		// Pause the receiving/sending for specified seconds
		usleep((recvsig[2] - 5)*1000);
	}
	
	return 0; 
} 

// Generate the simulated 3 phase power data
int phasegenerator(float *phasevals, float *recvsig) {
	int amplitude = 120;
	float phaseoffset = 2.0*M_PI/3.0;
	float randomnoise[3];
	randomnoise[0] = recvsig[0]*(random() % amplitude)/amplitude;
	randomnoise[1] = recvsig[0]*(random() % amplitude)/amplitude;
	randomnoise[2] = recvsig[0]*(random() % amplitude)/amplitude;

	phasevals[0] = amplitude*(sin(phasevals[3]) + randomnoise[0]);
	phasevals[1] = amplitude*(sin(phasevals[3] + phaseoffset) + randomnoise[1]);
	phasevals[2] = amplitude*(sin(phasevals[3] + 2*phaseoffset) + randomnoise[2]);
	phasevals[3] += recvsig[1];
	return 0;
}
