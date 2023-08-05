#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd) {
    char buff[MAX];
    int n;

    // Infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        
        // Read the message from the client and copy it in the buffer
        read(connfd, buff, sizeof(buff));
        
        // Print the buffer which contains the client's message
        printf("From client: %s\t To client: ", buff);
        bzero(buff, MAX);
        n = 0;
        
        // Copy server's message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // Send the buffer to the client
        write(connfd, buff, sizeof(buff));

        // If the message contains "exit", the server exits and chat ends
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now the server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    len = sizeof(cli);

    // Accept the data packet from the client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed...\n");
        exit(0);
    }
    else
        printf("Server accepted the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting, close the socket
    close(sockfd);

    return 0;
}
