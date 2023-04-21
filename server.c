#include "path.h"

int main(int argc, char* argv[])
{
    struct sockaddr_in serverAddress;
    struct sockaddr clientAddress;
    socklen_t clientAdressLen = sizeof(struct sockaddr);
    int fdSocket;
    ssize_t numRead;
    

    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = (in_port_t)htons(PORT_NUM);
    serverAddress.sin_addr.s_addr = (in_addr_t)htonl(INADDR_LOOPBACK);

    fdSocket = socket(AF_INET, SOCK_DGRAM, PORT_NUM);

    if(bind(fdSocket, (struct sockaddr*) &serverAddress, sizeof(struct sockaddr_in)) == -1)
        errExit("bind() main thread");

    while((numRead = recvfrom(fdSocket, buffer, 99, 0, &clientAddress, &clientAddress)) > 0) {
        write(STDOUT_FILENO, buffer, 99);
    }
}