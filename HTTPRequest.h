#ifndef server_h
#define server_h

#include "./DataStructures/Dictionary/Dictionary.h"

enum HTTPMethods {
    GET,
    POST,
    PUT,
    PATCH,
    DELETE,
    HEAD,
    OPTIONS,
    CONNECT,
    TRACE,
};

struct HTTPRequest {
    int Method;
    char *URI;
    float HTTPVersion;
    struct Dictionary header_fields;
};

struct HTTPRequest HTTPRequest_constructor(char *request_string);

#endif
