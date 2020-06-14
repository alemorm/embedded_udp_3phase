// #include <stdio.h> 
// #include <stdlib.h> 
// #include <math.h>
// #include <unistd.h> 
// #include <string.h> 
// #include <sys/types.h> 
// #include <sys/socket.h> 
// #include <arpa/inet.h> 
// #include <netinet/in.h> 

// #define PORT	 8080 
// #define MAXLINE 1024 
// #define M_PI 3.14159265358979323846

// // Driver code 
// int main() {
// 	int sockfd;
// 	char buffer[10];
// 	double sinevals[1];
// 	struct sockaddr_in servaddr, cliaddr;

// 	// Creating socket file descriptor 
// 	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
// 		perror("socket creation failed"); 
// 		exit(EXIT_FAILURE);
// 	} 
	
// 	memset(&servaddr, 0, sizeof(servaddr)); 
// 	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
// 	// Filling server information 
// 	servaddr.sin_family = AF_INET; // IPv4 
// 	servaddr.sin_addr.s_addr = INADDR_ANY; 
// 	servaddr.sin_port = htons(PORT); 
	
// 	// Bind the socket with the server address 
// 	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
// 			sizeof(servaddr)) < 0 ) 
// 	{ 
// 		perror("bind failed"); 
// 		exit(EXIT_FAILURE); 
// 	} 
	
// 	int len, n; 

// 	len = sizeof(cliaddr); //len is value/result 

// 	// while (1)
// 	// {
// 		n = recvfrom(sockfd, (char *)buffer, 10, 
// 				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
// 				&len); 
// 		// buffer[n] = '\0'; 
// 		printf("Client : %s\n", buffer); 
// 		// sinevals[0] = sin(0);
// 		// sinevals[1] = sin(M_PI*(2.0/3));
// 		// sinevals[2] = sin(M_PI*(4.0/3));
// 		// sinevals[0] = 1.5;
// 		sinevals[1] = 2.5;
// 		// sinevals[2] = 3.5;
// 		printf("Server : %f\n", sinevals[0]);
// 		// printf("Server : %f \t %f \t %f\n", sinevals[0], sinevals[1], sinevals[2]);
// 		sendto(sockfd, (const double *)sinevals, sizeof(sinevals), 
// 			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
// 				len); 
// 		printf("Hello message sent.\n");
// 	// } 
	
// 	return 0; 
// } 

// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8050 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	int sockPC;
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	if ( (sockPC = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
		
	int len, n; 

	len = sizeof(cliaddr); //len is value/resuslt 

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Client : %s\n", buffer); 
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	printf("Hello message sent.\n"); 
	
	return 0; 
} 
