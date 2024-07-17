#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdbool.h>
#include "soll.h"

// Define string representations for SOLL types
#define SOLLTYPE_NONE "none"
#define SOLLTYPE_MTF "mtf"
#define SOLLTYPE_TRANSPOSE "transpose"

// Function to get SOLL type as string
const char* get_solltype_name(orgtype type);

// Forward declaration of node struct
typedef struct Node Node;

// Definition of node struct
struct Node {
    char *data;
    Node *next;
    Node *prev;
    int frequency;
};

void move_to_front(soll *s, Node *node);

void transpose(soll *s, Node *node);

#endif
