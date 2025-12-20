#include <string.h>
#include <stdarg.h>
#include "HTTPServer.h"
#include "Route.h"



// x     → value
// &x    → address
// ptr   → address
// *ptr  → value at address
void register_routes(struct HTTPServer *server, void (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...);

void launch(struct Server *);

struct HTTPServer http_server_constructor(){
    struct HTTPServer server;
    server.server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 255, launch);
    server.routes = dictionary_constructor(compare_string_keys);
    server.register_routes = register_routes;
    
    return server;
};

void register_routes(struct HTTPServer *server, void (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...){
    struct Route route;
    va_list methods;
    va_start(methods, num_methods);
    for (int i = 0; i < num_methods; i++) {
        route.methods[i] = va_arg(methods, int);
    }
    strcpy(route.uri, uri);
    route.route_function = route_function;

    server->routes.insert(&server->routes, uri, sizeof(char[strlen(uri)]), &route, sizeof(route));
}



























































// void retrieve_page(struct HTTPRequest request, int socket);

// void launch_httpserver(struct Server *server);

// void launch_httpserver(struct Server *server){
//     int addrlen = sizeof(server->address);
//     long valread;
//     while(1){
//         printf("===== waiting ===== \n");
//         int new_socket = accept(server->socket , (struct sockaddr *)&server->address, (socklen_t *)&addrlen);
//         char buffer[30000];
//         valread = read(new_socket, buffer, 30000);
//         struct HTTPRequest request = http_request_constructor(buffer);
//         retrieve_page(request, new_socket);
//         close(new_socket);
//     }
// }

// void retrieve_page(struct HTTPRequest request, int socket){
//     char path[30000] = {0};

//     char *url = strtok(request.request_line.search(&request.request_line, "uri"), "?");
//     char *vars = strtok(NULL, "\0");

//     strcpy(path, "/home/sbj/Desktop");
//     if(strcmp(url, "/test") == 0){
//         strcat(path, url);
//     } else {
//         strcat(path, "/index");
//     }
//     strcat(path, ".html");

//     FILE *f = fopen(path, "r");
//     fseek(f, 0, SEEK_END);
//     long fsize = ftell(f);
//     fseek(f, 0, SEEK_SET);

//     char *buffer = malloc(fsize + 1);
//     fread(buffer, 1, fsize, f);
//     fclose(f);

//     char response[30000] = {0};
//     strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
//     strcat(response, buffer);
//     write(socket, response, strlen(response));

// }