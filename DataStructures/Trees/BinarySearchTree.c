#include "BinarySearchTree.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Node * create_node_bst(void *data, int size);
void destroy_node_bst(struct Node *node_to_destroy);
void recursive_tree_destruction(struct Node *node);

void insert_bst(struct BinarySearchTree *tree, void *data, int size);
void * search_bst(struct BinarySearchTree *tree, void *data);

struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two)){
    struct BinarySearchTree tree;

    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;
    return tree;
};


struct Node * create_node_bst(void *data, int size){
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

void destroy_node_bst(struct Node *node_to_destroy){
    node_destructor(node_to_destroy);
}

// depth first binary tree traversal
void recursive_tree_destruction(struct Node *node){
    if (node->prev){
        recursive_tree_destruction(node->prev);
    }
    if(node->next){
        recursive_tree_destruction(node->next);
    }
    destroy_node_bst(node);
}

void binary_search_tree_destructor(struct BinarySearchTree tree){
    recursive_tree_destruction(tree.head);
}
struct Node * iterate_bst(struct BinarySearchTree *tree, struct Node *cursor, void *data, int *direction){
    if((tree->compare(cursor->data, data) == 1)){
        if(cursor->next){
            return iterate_bst(tree, cursor->next, data, direction);
        } else {
            *direction = 1;
            return cursor;
        }
    } else if((tree->compare(cursor->data, data) == -1)){
        if(cursor->prev){
            return iterate_bst(tree, cursor->prev, data, direction);
        } else {
            *direction = -1;
            return cursor;
        }
    } else {
        direction = 0;
        return cursor;
    }
}

void * search_bst(struct BinarySearchTree *tree, void *data){
    int direction = 0;
    struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);
    if(direction == 0){
        return cursor->data;
    } else {
        return NULL;
    }
}

void insert_bst(struct BinarySearchTree *tree, void *data, int size){
    if(!tree->head){
        tree->head = create_node_bst(data, size);
    } else {
        int direction = 0;
        struct Node *cursor = iterate_bst(tree, tree->head, data, &direction);
        if(direction == 1){
            cursor->next = create_node_bst(data, size);
        } else if (direction == -1){
            cursor->prev = create_node_bst(data, size);
        }
    }
}
