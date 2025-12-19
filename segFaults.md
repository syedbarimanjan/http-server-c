# Segmentation Fault 1
There is a bug in the httpserver.c file where i am passing something wrong to a function. spent 1 hour 25min on 18 dec to resolve it.
```
#0  compare_string_keys (entry_one=0x406780, entry_two=0x7fffffff5cf0) at ./DataStructures/Dictionary/Dictionary.c:51
#1  0x0000000000401d1e in iterate_bst (tree=0x7fffffff5d30, cursor=0x406760, data=0x7fffffff5cf0, direction=0x7fffffff5cb4)
    at ./DataStructures/Trees/BinarySearchTree.c:48
#2  0x0000000000401e6f in insert_bst (tree=0x7fffffff5d30, data=0x7fffffff5cf0, size=16) at ./DataStructures/Trees/BinarySearchTree.c:83
#3  0x0000000000401735 in insert_dictionary (dictionary=0x7fffffff5d30, key=0x402814, key_size=4, value=0x7fffffff5d14, value_size=1)
    at ./DataStructures/Dictionary/Dictionary.c:47
#4  0x0000000000400fd8 in extract_request_line_fields (request=0x7fffffff6080, request_line=0x7fffffff5db0 "GET / HTTP/1.1\r") at HTTPRequest.c:120
#5  0x0000000000400d81 in http_request_constructor (
    request_string=0x7fffffff6200 "GET / HTTP/1.1\r\nHost: localhost:8080\r\nConnection: keep-alive\r\nsec-ch-ua: \"Chromium\";v=\"142\", \"Google Chrome\";v=\"142\", \"Not_A Brand\";v=\"99\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Linux\"\r\nUpgrade-I"...) at HTTPRequest.c:89
#6  0x000000000040081c in launch_httpserver (server=0x7fffffffd770) at HTTPServer.c:22
#7  0x000000000040064d in main () at test.c:23
```