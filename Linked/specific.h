#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdbool.h>
#include "../soll.h"

// String representations for SOLL types.
#define SOLLTYPE_NONE "none"
#define SOLLTYPE_MTF "mtf"
#define SOLLTYPE_TRANSPOSE "transpose"

#define SOLLTYPE get_solltype()

struct Node {
    char *data;
    struct Node *next;
    struct Node *prev;
    int frequency;
};

struct soll {
    Node *head;
    Node *tail;
    int size;
    orgtype type;
    const char* solltype_string;
};

const char* get_solltype(void);
void set_solltype(orgtype type);
const char* get_solltype_name(orgtype type);

Node* create_node(const char* str);
Node* find_node(soll* s, char* str, long* cnt);

void move_to_front(soll *s, Node *node);
void transpose_node(soll* s, Node* node);

void print_list(soll* s);
void assert_list_integrity(soll* s);

#endif
