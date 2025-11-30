#ifndef server_h
#define server_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    void(*launch)(void);
};

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(void));

#endif
