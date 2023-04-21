#include "path.h"


int main(int argc, char* argv[])
{
    struct sockaddr_in serverAddress;
    int fdSocket;
    ssize_t numRead;
    

    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = (in_port_t)htons(PORT_NUM);
    serverAddress.sin_addr.s_addr = (in_addr_t)htonl(INADDR_LOOPBACK);

    fdSocket = socket(AF_INET, SOCK_DGRAM, 0);


    while((numRead = read(STDIN_FILENO, buffer, 99)) > 0) {
        sendto(fdSocket, buffer, 99, 0, (struct sockaddr*) &serverAddress,sizeof(struct sockaddr_in));

    }

    close(fdSocket);

    exit(EXIT_SUCCESS);
}