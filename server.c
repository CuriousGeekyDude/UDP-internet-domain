#include "path.h"

int main(int argc, char* argv[])
{
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(struct sockaddr_in);
    int fdSocket;
    ssize_t numRead;
    char clientAddr[INET_ADDRSTRLEN] = "";

    

    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = (in_port_t)htons(PORT_NUM);
    serverAddress.sin_addr.s_addr = (in_addr_t)htonl(INADDR_LOOPBACK);

    fdSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(fdSocket == -1)
        errExit("socket() server");

    if(bind(fdSocket, (struct sockaddr*) &serverAddress, sizeof(struct sockaddr_in)) == -1)
        errExit("bind() server");

    while((numRead = recvfrom(fdSocket, buffer, 99, 0, (struct sockaddr*)&clientAddress, &clientAddressLen)) > 0) {
        const char* ptr = inet_ntop(AF_INET, (struct in_addr*)&(clientAddress.sin_addr), clientAddr, INET_ADDRSTRLEN);
        printf("%s: ", clientAddr);
        fflush(stdout);                 //In order to make sure that the client address gets printed in the terminal
        write(STDOUT_FILENO, buffer, 99);
    }

    close(fdSocket);

    exit(EXIT_SUCCESS);
}