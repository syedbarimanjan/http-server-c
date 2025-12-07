#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

void launch(struct Server *server) {
    while(1) {
        char buffer[30000];
        printf("=============== WAITING for CONNECTION ===============\n");
        int address_length = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address , (socklen_t *)&address_length);
        read(new_socket,buffer,30000);
        printf("%s\n", buffer);
        char *hello = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\nContent-Length: 45\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html><body><h1>Hello World</h1></body></html>";
        write(new_socket,hello,strlen(hello));
        close(new_socket);
    }
}

int main() {
    struct Server server = server_constructor(AF_INET,SOCK_STREAM,0,INADDR_ANY,8080,10,launch);
    server.launch(&server);
}
