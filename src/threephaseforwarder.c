/* threephaseforwarder.c */
#include <stdio.h> 
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
	// servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_addr.s_addr = inet_addr(REMOTE_IP); 
	
	int n, len; 
	
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("Hello message sent.\n"); 
		
	// n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
	// 			MSG_WAITALL, (struct sockaddr *) &servaddr, 
	// 			&len); 
	// buffer[n] = 
	// printf("Server : %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 

