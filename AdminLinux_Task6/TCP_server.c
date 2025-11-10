#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/ip.h>

#include <unistd.h>

#include <stdio.h>

#define PORT_NUMBER 8000

int main(int argc, char const *argv[])
{
    int error_state;
    // AF_INET = IPv4 , SOCK_STREAM = full duplex , SOCK_CLOEXEC = dont inherint socket to child processes
    // protocol 6 = TCP (found in /etc/protocols)
    int nfd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 6);

    // create socket address struct (port, address = any address)
    struct sockaddr_in mysocket_addr;
    mysocket_addr.sin_family = AF_INET;
    mysocket_addr.sin_port = htons(PORT_NUMBER);
    mysocket_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // bind (assign an address and port) to the the socket fd
    // we need to cast sockaddr_in to sockaddr
    bind(nfd, (struct sockaddr *)&mysocket_addr, sizeof(mysocket_addr));

    // listen to the port
    error_state = listen(nfd, 2);
    if (0 != error_state)
    {
        printf("failed to listen .\n");
        return 1;
        close(nfd);
    }
    else
    {
        printf("listening to 127.0.0.1:%d\n", PORT_NUMBER);
    }
    // accept connection of client
    int addr_length = sizeof(mysocket_addr);
    int newfd = accept(nfd, (struct sockaddr *)&mysocket_addr, &addr_length);
    if (-1 == newfd)
    {
        printf("failed to accept.\n");
        return 1;
        close(nfd);
    }
    else
    {
        printf("accepted client from 127.0.0.1:%d\n", PORT_NUMBER);
    }

    int numbers_received[2] = {0};
    int result = 0;
    while (1)
    {

        error_state = recv(newfd, numbers_received, sizeof(numbers_received), 0);
        if (0 == error_state)
        {
            printf("client disconnected.\n");
            break;
        }
        else if (-1 == error_state)
        {
            printf("error while receiving.\n");
            break;
        }
        else
        {
        printf("Received %d , %d from client\n", numbers_received[0], numbers_received[1]);

        result = numbers_received[0] + numbers_received[1];
        printf("Sum Result =%d \n", result);

        send(newfd, &result, sizeof(result), 0);
        }
    }

    close(nfd);
    return 0;
}
