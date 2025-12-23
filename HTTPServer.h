#ifndef HTTPServer_h
#define HTTPServer_h

#include "server.h"
#include "HTTPRequest.h"

struct HTTPServer {
    struct Server server;
    struct Dictionary routes;
    void (*register_routes)(struct HTTPServer *server, char * (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...);
};

struct HTTPServer http_server_constructor(void);
// void launch_httpserver(struct Server *server);

#endif
