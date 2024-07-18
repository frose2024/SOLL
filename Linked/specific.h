#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdbool.h>
#include "../soll.h"

// Define string representations for SOLL types.
#define SOLLTYPE_NONE "none"
#define SOLLTYPE_MTF "mtf"
#define SOLLTYPE_TRANSPOSE "transpose"

// Function to get SOLL type as string.
const char* get_solltype_name(orgtype type);

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
};

Node* create_node(const char* str);

void move_to_front(soll *s, Node *node);

void trans(soll *s, Node *node);

#endif
