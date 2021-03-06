#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "info.h"

int main(void)
{
    int sockfd = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Can't open socket!");
        exit(1);
    }

    struct sockaddr server_addr;
    server_addr.sa_family = AF_UNIX;
    strcpy(server_addr.sa_data, SOCKET_NAME);

    char msg[MSG_LEN]; 
    sprintf(msg, "Client with pid send msg %d\n", getpid());
    sendto(sockfd, msg, strlen(msg), 0, &server_addr, sizeof(server_addr));

    close(sockfd);
    return 0;
}
