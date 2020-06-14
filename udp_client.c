// #include <stdio.h> 
// #include <stdlib.h> 
// #include <unistd.h> 
// #include <string.h> 
// #include <sys/types.h> 
// #include <sys/socket.h> 
// #include <arpa/inet.h> 
// #include <netinet/in.h> 

// #define PORT	 8080 
// #define MAXLINE 1024 

// typedef struct sinevals{ 
//          float firstval; 
//          float secondval; 
//          float thirdval;
// } threephasepower;

// // Driver code 
// int main() { 
// 	int sockfd; 
// 	// char buffer[MAXLINE];
// 	double buffer[3];
// 	// char *hello = "testing client"; 
// 	int hello[1] = 5;
// 	struct sockaddr_in	 servaddr; 
// 	threephasepower sine_struct;

// 	// Creating socket file descriptor 
// 	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
// 		perror("socket creation failed"); 
// 		exit(EXIT_FAILURE); 
// 	} 

// 	memset(&servaddr, 0, sizeof(servaddr)); 
	
// 	// Filling server information 
// 	servaddr.sin_family = AF_INET; 
// 	servaddr.sin_port = htons(PORT); 
// 	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
// 	int n, len; 
	
// 	sendto(sockfd, (const int *)hello, sizeof(hello), 
// 		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
// 			sizeof(servaddr));
// 	printf("Testing client.\n");
		
// 	n = recvfrom(sockfd, (double *)buffer, sizeof(buffer), 
// 				MSG_WAITALL, (struct sockaddr *) &servaddr, 
// 				&len);

// 	// n = recvfrom(sockfd, (const) &sine_struct, sizeof(sine_struct), 
// 	// 			0, (struct sockaddr *) &servaddr, 
// 	// 			&len); 

// 	// sine_struct.firstval  = ntohl((uint32_t)sine_struct.firstval );
// 	// sine_struct.secondval = ntohl((uint32_t)sine_struct.secondval);
// 	// sine_struct.thirdval  = ntohl((uint32_t)sine_struct.thirdval );
// 	// buffer[n] = '\0'; 
// 	// printf("Server : %s\n", buffer); 
// 	printf("Server : %f \t %f \t %f\n", buffer[0], buffer[1], buffer[2]);
// 	// printf("Server : %f \t %f \t %f\n", sine_struct.firstval, sine_struct.secondval, sine_struct.thirdval); 

// 	close(sockfd); 
// 	return 0; 
// } 

// Client side implementation of UDP client-server model 
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
	char buffer[MAXLINE]; 
	char *hello = "Hello from client"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("Hello message sent.\n"); 
		
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = 
	printf("Server : %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 

