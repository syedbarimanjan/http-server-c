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
    // int Method;
    // char *URI;
    // float HTTPVersion;
    struct Dictionary header_fields;
    struct Dictionary request_line;
    struct Dictionary body;
};

struct HTTPRequest http_request_constructor(char *request_string);
void http_request_destructor(struct HTTPRequest *request);

#endif
