#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdbool.h>
#include "../soll.h"

// String representations for SOLL types.
#define SOLLTYPE_NONE "none"
#define SOLLTYPE_MTF "mtf"
#define SOLLTYPE_TRANSPOSE "transpose"

// Macro to get SOLL type as string
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

// Function to set+get SOLL type
const char* get_solltype_name(orgtype type);
const char* get_solltype(void);
void set_solltype(orgtype type);

Node* create_node(const char* str);

void move_to_front(soll *s, Node *node);
void trans(soll *s, Node *node);

Node* find_node(soll* s, char* str, long* cnt);
void move_to_front(soll* s, Node* node);
void transpose_node(soll* s, Node* node);
void print_list(soll* s);

#endif
