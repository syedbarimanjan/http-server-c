#include "HTTPRequest.h"
#include <unistd.h>
#include <string.h>

#include "./DataStructures/Lists/Queue.h"
#include "DataStructures/Dictionary/Dictionary.h"

int method_select(char *method){
    if(strcmp(method, "GET") == 0){
        return GET;
    }
    else if(strcmp(method, "POST") == 0){
        return POST;
    }
    else if(strcmp(method, "PUT") == 0){
        return PUT;
    }
    else if(strcmp(method, "PATCH") == 0){
        return PATCH;
    }
    else if(strcmp(method, "DELETE") == 0){
        return DELETE;
    }
    else if(strcmp(method, "OPTIONS") == 0){
        return OPTIONS;
    }
    else if(strcmp(method, "CONNECT") == 0){
        return CONNECT;
    }
    else if(strcmp(method, "HEAD") == 0){
        return HEAD;
    }
    else if(strcmp(method, "TRACE") == 0){
        return TRACE;
    }
    else {
        return -1;
    }
};

void extract_request_line_fields(struct HTTPRequest *request, char *line_fields);
void extract_header_fields(struct HTTPRequest *request, char *header_fields);
void extract_body(struct HTTPRequest *request, char *body);

struct HTTPRequest http_request_constructor(char *request_string) {
    struct HTTPRequest request;

    char requested[strlen(request_string)];
    strcpy(requested, request_string);

    for (int i = 0; i < strlen(requested) - 2; i++) {
        if(requested[i] == '\n' && requested[i + 1] == '\n') {
            requested[i + 1] = '|';
        }
    }

    char *request_line = strtok(requested, "\n");
    char *heador_fields = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    // char *method = strtok(request_line," ");
    // request.Method = method_select(request_line);
    // char *URI = strtok(NULL, " ");
    // request.URI = URI;
    // char *HTTPVersion = strtok(NULL, " ");
    // HTTPVersion = strtok(HTTPVersion, "/");
    // HTTPVersion = strtok(NULL, "/");
    // request.HTTPVersion = (float)atof(HTTPVersion);

    // request.header_fields = dictionary_constructor(compare_string_keys);

    // struct Queue headers = queue_constructor();

    // char *token = strtok(heador_fields, "\n");
    // while(token){
    //     headers.push(&headers, token, sizeof(*token));
    //     token = strtok(NULL, "\n");
    // }

    // char *header = (char *)headers.peek(&headers);
    // while(header){
    //     char *key = strtok(header, ":");
    //     char *value = strtok(NULL, "|");
    //     request.header_fields.insert(&request.header_fields,key, sizeof(*key), value,sizeof(*value));
    //     headers.pop(&headers);
    //     header = (char *)headers.peek(&headers);
    // }

    extract_request_line_fields(&request, request_line);
    extract_header_fields(&request, heador_fields);
    extract_body(&request, body);

    return request;
}

void http_request_destructor(struct HTTPRequest *request){
    dictionary_destructor(&request->request_line);
    dictionary_destructor(&request->header_fields);
    dictionary_destructor(&request->body);
}

void extract_request_line_fields(struct HTTPRequest *request, char *request_line){
    char fields[strlen(request_line)];
    strcpy(fields, request_line);

    char *method = strtok(fields," ");
    // request.Method = method_select(request_line);
    char *uri = strtok(NULL, " ");
    // request.URI = URI;
    char *http_version = strtok(NULL, "\0");
    // HTTPVersion = strtok(HTTPVersion, "/");
    // HTTPVersion = strtok(NULL, "/");
    // request.HTTPVersion = (float)atof(HTTPVersion);
    struct Dictionary request_line_dict = dictionary_constructor(compare_string_keys);
    request_line_dict.insert(&request_line_dict, "method", sizeof("method"), method, sizeof(char[strlen(method)]));
    request_line_dict.insert(&request_line_dict, "uri", sizeof("uri"), uri, sizeof(char[strlen(uri)]));
    request_line_dict.insert(&request_line_dict, "http_version", sizeof("http_version"), http_version, sizeof(char[strlen(http_version)]));

    request->request_line = request_line_dict;
    //add sizeof to dict search
    if(request->request_line.search(&request->request_line, "GET")){
        extract_body(request, (char *)request->request_line.search(&request->request_line, "uri"));
    }
}

void extract_header_fields(struct HTTPRequest *request, char *header_fields){
    char fields[strlen(header_fields)];
    strcpy(fields, header_fields);

    struct Queue headers = queue_constructor();

    char *field = strtok(fields, "\n");
    while(field){
        headers.push(&headers, field, sizeof(char[strlen(field)]));
        field = strtok(NULL, "\n");
    }

    request->header_fields = dictionary_constructor(compare_string_keys);

    char *header = (char *)headers.peek(&headers);
    while(header){
        char *key = strtok(header, ":");
        char *value = strtok(NULL, "\0");
        if(value){
            if(value[0] == ' '){
                value++;
            }
            request->header_fields.insert(&request->header_fields, key, sizeof(char[strlen(key)]), value, sizeof(char[strlen(value)]));
        }
        headers.pop(&headers);
        header = (char *)headers.peek(&headers);
    }
    queue_destructor(&headers);
}

void extract_body(struct HTTPRequest *request, char *body){
    // add sizeof to search sizeof("Content-Type")
    char *content_type = (char *)request->header_fields.search(&request->header_fields, "Content-Type");
    if(content_type){
        struct Dictionary body_fields = dictionary_constructor(compare_string_keys);
        if (strcmp(content_type, "application/x-www-form-urlencoded") == 0){
            struct Queue fields = queue_constructor();
            char *field = strtok(body, "&");
            while (field){
                fields.push(&fields, field, sizeof(char[strlen(field)]));
            }
            field = fields.peek(&fields);
            while (field) {
                char *key = strtok(field, "=");
                char *value = strtok(NULL, "\0");
                if(value[0] == ' '){
                    value++;
                }
                body_fields.insert(&body_fields, key, sizeof(char[strlen(key)]), value, sizeof(char[strlen(value)]));
                fields.pop(&fields);
                field = fields.peek(&fields);
            }
            queue_destructor(&fields);
        } else {
            body_fields.insert(&body_fields, "data", sizeof("data"), body, sizeof(char[strlen(body)]));
        }
        request->body = body_fields;
    }
}
