#ifndef HTTPServer_h
#define HTTPServer_h

#include "server.h"
#include "HTTPRequest.h"

struct HTTPServer {
    struct Server server;
    struct Dictionary routes;
    void(*launch)(struct HTTPServer *server);
};

struct HTTPServer http_server_constructor(void);
void launch_httpserver(struct Server *server);

#endif
