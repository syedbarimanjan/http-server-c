#ifndef Dictionary_h
#define Dictionary_h

struct Dictionary {
    int key;
    void *Data;
    int hash;

    void(*lookup)();
};

#endif
