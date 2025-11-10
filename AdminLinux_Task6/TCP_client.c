#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define PORT_NUMBER 8000

int main(int argc, char const *argv[])
{
    int error_state;
    // AF_INET = IPv4 , SOCK_STREAM = full duplex , SOCK_CLOEXEC = dont inherint socket to child processes
    // protocol 6 = TCP (found in /etc/protocols)
    int nfd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 6);
    if (nfd == -1)
    {
        printf("Failed to create socket: %s\n", strerror(errno));
        return 1;
    }
    // create socket address struct (port, address = any address)
    struct sockaddr_in mysocket_addr;
    mysocket_addr.sin_family = AF_INET;
    mysocket_addr.sin_port = htons(PORT_NUMBER);
    mysocket_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // connect to the server
    error_state = connect(nfd, (struct sockaddr *)&mysocket_addr, sizeof(mysocket_addr));
    if (0 != error_state)
    {
        printf("failed to connect to server.\n");
        return 1;
        close(nfd);
    }
    else
    {
        printf("Connected to 127.0.0.1:%d\n", PORT_NUMBER);
    }
    int numbers[2]={0} ;
    int received=0;
    while (1)
    {
        printf("Enter first number (or -1 to exit): \n");
        scanf("%d", &numbers[0]);
        if (-1 == numbers[0])
        {
            break;
        }
        printf("Enter second number: \n");
        scanf("%d", &numbers[1]);
        
        error_state = send(nfd, numbers, sizeof(numbers), 0);
        if (-1 == error_state)
        {
            printf("failed to send to server.\n");
        }
        else
        {
            printf("Sent %d , %d to server.\n", numbers[0], numbers[1]);
        }

        recv(nfd, &received, sizeof(received), 0);
        printf("Received %d from server\n", received);
    }
    close(nfd);
    return 0;
}
