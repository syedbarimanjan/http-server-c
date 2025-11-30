#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

void launch(struct Server *server)
{
    char buffer[30000];
    printf("=============== WAITING for CONNECTION ===============");
    int address_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address , (socklen_t *)&address_length);
    read(new_socket,buffer,30000);
}

int main()
{
    struct Server server = server_constructor(AF_INET,SOCK_STREAM,0,INADDR_ANY,80,10);
}
