#ifndef Dictionary_h
#define Dictionary_h

#include "../Trees/BinarySearchTree.h"
#include "Entry.h"
struct Dictionary {
    struct BinarySearchTree binary_search_tree;

    void (*insert)(struct Dictionary *dictionary,void *key, int key_size, void *value, int value_size);
    void *(*search)(struct Dictionary *dictionary,void *key);
};

struct Dictionary dictionary_constructor(int (*compare)(void *key_one, void *key_two));
struct Dictionary dictionary_destructor(struct Dictionary *dictionary);

#endif
