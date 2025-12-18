#include "HTTPServer.h"
#include "HTTPRequest.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void retrieve_page(struct HTTPRequest request, int socket);

// void launch_httpserver(struct Server *server);

void launch_httpserver(struct Server *server){
    int addrlen = sizeof(server->address);
    long valread;
    while(1){
        printf("===== waiting ===== \n");
        int new_socket = accept(server->socket , (struct sockaddr *)&server->address, (socklen_t *)&addrlen);
        char buffer[30000];
        valread = read(new_socket, buffer, 30000);
        struct HTTPRequest request = http_request_constructor(buffer);
        retrieve_page(request, new_socket);
        close(new_socket);
    }
}

void retrieve_page(struct HTTPRequest request, int socket){
    char path[30000] = {0};

    char *url = strtok(request.request_line.search(&request.request_line, "uri"), "?");
    // char *vars = strtok(NULL, "\0");

    strcpy(path, "/home/sbj/Desktop");
    if(strcmp(url, "/test") == 0){
        strcat(path, url);
    } else {
        strcat(path, "/index");
    }
    strcat(path, ".html");

    FILE *f = fopen(path, "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, f);
    fclose(f);

    char response[30000] = {0};
    strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    strcat(response, buffer);
    write(socket, response, strlen(response));

}
// x     → value
// &x    → address
// ptr   → address
// *ptr  → value at address
