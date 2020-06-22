/* threephaseforwarder.c */
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
#define GEN_PORT 5367
#define PY_PORT 6367
#define MAXLINE 1024 

int main() { 
	int sockpifd, sockpcfd, n, clilen, servlen, genlen, pylen;
	float phasevals[3], pythonargs[2];
	char clientaddress[40], serveraddress[40];
	int udpdelay = 1000.0/60.0;  //60 Hz frequency
	struct sockaddr_in servaddr, cliaddr, genaddr, pyaddr;
	
	// Creating socket file descriptors 
	if ((sockpifd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ||
	 	(sockpcfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	// Set the datagram memory value to 0
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	memset(&genaddr, 0, sizeof(genaddr)); 
	
	// Listening UDP server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_port = htons(PY_PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY;

	// 3 Phase Generator setup
	genaddr.sin_family = AF_INET;
	genaddr.sin_port = htons(GEN_PORT);
	inet_aton(LOCAL_IP, &genaddr.sin_addr);
	
	// Python client setup
	pyaddr.sin_family = AF_INET;
	pyaddr.sin_port = htons(PY_PORT);
	inet_aton(REMOTE_IP, &pyaddr.sin_addr);
	
	// Bind the socket with the server address 
	if ( bind(sockpcfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	// Get size of datagrams
	clilen = sizeof(cliaddr); //len is value/result 
	servlen = sizeof(servaddr); //len is value/result 
	genlen = sizeof(genaddr); //len is value/result 
	pylen = sizeof(pyaddr); //len is value/result 

	// Listen for start signal from python client
	n = recvfrom(sockpcfd, (float *)pythonargs, sizeof(pythonargs), 
				0, ( struct sockaddr *) &cliaddr, 
				&clilen); 

	inet_ntop(AF_INET, &cliaddr.sin_addr, clientaddress, sizeof(clientaddress));

	// Print python client information
	printf("Length = %d\n", n);
	printf("Receive noise = %f\n", pythonargs[0]);
	printf("Receive timestep = %f\n", pythonargs[1]);
	printf("Python address = %s\n", clientaddress);
	printf("Python port = %d\n", htons(cliaddr.sin_port));

	// Send start signal to generator server
	sendto(sockpifd, (const float *)pythonargs, sizeof(pythonargs), 
			0, (const struct sockaddr *) &genaddr, 
				genlen); 

	inet_ntop(AF_INET, &genaddr.sin_addr, serveraddress, sizeof(serveraddress));

	// Print generator server information
	printf("Send noise = %f\n", pythonargs[0]);
	printf("Send timestep = %f\n", pythonargs[1]);
	printf("Generator address = %s\n", serveraddress);
	printf("Generator port = %d\n", htons(genaddr.sin_port));

	while(1) {
		// Receive simulated 3 phase power data from generator server
		n = recvfrom(sockpifd, (float *)phasevals, sizeof(phasevals), 
				0, ( struct sockaddr *) &genaddr, 
				&genlen); 
		
		// Relay simulated 3 phase power data to python client
		sendto(sockpcfd, (const float *)phasevals, sizeof(phasevals), 
			0, (const struct sockaddr *) &pyaddr, 
				pylen); 

		// Debug print
		// printf("Phase values : %f\t%f\t%f\n", phasevals[0], phasevals[1], phasevals[2]);
		
		// Pause the receiving/sending for 0.1 seconds
		usleep(udpdelay*1000);
	}
	
	return 0; 
} 
