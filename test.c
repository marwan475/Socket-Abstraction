#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>      // for inet_aton()
#include <netinet/in.h>

#define MAX_BUF 512

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;
    int destport = 8888;
    char destip[] = "192.168.1.20";
    char sendbuf[MAX_BUF];

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure destination address structure
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(destport);
    if (inet_aton(destip, &dest_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address: %s\n", destip);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Ask user for the message
    printf("Please, type your message: ");
    if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send the message using UDP
    if (sendto(sockfd, sendbuf, strlen(sendbuf), 0,
               (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(sockfd);
    return 0;
}

