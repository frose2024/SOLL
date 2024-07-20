#include "specific.h"


static const char* current_solltype;

const char* get_solltype(void) {
    return current_solltype;
}

void set_solltype(orgtype type) {
    switch (type) {
        case none:
            current_solltype = SOLLTYPE_NONE;
            break;
        case mtf:
            current_solltype = SOLLTYPE_MTF;
            break;
        case transpose:
            current_solltype = SOLLTYPE_TRANSPOSE;
            break;
        default:
            current_solltype = "unknown";
            break;
    }
}

const char* get_solltype_name(orgtype type) {
    switch (type) {
        case none:
            return SOLLTYPE_NONE;
        case mtf:
            return SOLLTYPE_MTF;
        case transpose:
            return SOLLTYPE_TRANSPOSE;
        default:
            return "unknown";
    }
}

soll* soll_init(orgtype type) {
     // Allocate memroy for SOLL struct. 
    soll* s = (soll*)malloc(sizeof(soll));                 
    if (!s) {
        fprintf(stderr, "Memory allocation failed\n");     
        exit(EXIT_FAILURE);
    }
    s->head = NULL;                                         
    s->tail = NULL;                                         
    s->size = 0;                                           
    s->type = type;
    s->solltype_string = get_solltype_name(type);                                                                      
    return s;                                               
}

// Function to create new node.
Node* create_node(const char* str) {
    Node* new_node = (Node*)malloc(sizeof(Node));           
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");          
        exit(EXIT_FAILURE);
    }
    // Allocate memory for data + copy the string. 
    new_node->data = strdup(str);                               
    if (!new_node->data) {
        fprintf(stderr, "Memory allocation failed\n");          
        free(new_node);
         // Free the node + exit if memory allocation fails. 
        exit(EXIT_FAILURE);                                    
    }
    new_node->next = NULL;                                      
    new_node->prev = NULL;                                      
    new_node->frequency = 1;                                   
    return new_node;                                         
}                       

// Implement soll_add - add element to the list.
void soll_add(soll* s, char* str) {
     // If SOLL is null, do nothing.
    if (!s) return;                                            
    Node* new_node = create_node(str);     
    // If list empty, set head+tail to new node.                      
    if (!s->head) {                                             
        s->head = s->tail = new_node;   
        // If list !empty, add new node to end of list.                             
    } else {                                                    
        s->tail->next = new_node;
        new_node->prev = s->tail;
        s->tail = new_node;
    }
    s->size++;                                         
}

// Implement soll_free - free allocated memory.
bool soll_free(soll* s) {
    if (!s) return true;
    Node* current = s->head;
    while (current) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    free(s);
    return true;
}

// Implement soll_remove - remove element from the list.
bool soll_remove(soll* s, char* str) {
    if (!s || !str) return false;
    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                s->head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                s->tail = current->prev;
            }
            free(current->data);
            free(current);
            s->size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Node helper function. Find node, count pointer chases. 
Node* find_node(soll* s, char* str, long* cnt) {
    if (!s || !str) return NULL;

    Node* current = s->head;
    *cnt = 0;

    while (current) {
        (*cnt)++;
        if (strcmp(current->data, str) == 0) {
            current->frequency++;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// MTF function. Moves the node. 
void move_to_front(soll* s, Node* node) {
    if (node == s->head) return;

    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        s->tail = node->prev;
    }
    node->next = s->head;
    s->head->prev = node;
    node->prev = NULL;
    s->head = node;
}

// Tranpose function. Swaps the nodes.
void transpose_node(soll* s, Node* node) {
    if (node == s->head || !node->prev) {
        return;
    }
    Node* prev = node->prev;
    Node* prevprev = prev->prev;
    Node* next = node->next;

    // Remove node from current position
    if (next) {
        next->prev = prev;
    } else {
        s->tail = prev;
    }
    prev->next = next;

    // Insert node in front of prev
    node->next = prev;
    node->prev = prevprev;
    prev->prev = node;
    if (prevprev) {
        prevprev->next = node;
    } else {
        s->head = node;
    }
}

// Print list for debug purposes. 
void print_list(soll* s) {
    Node* current = s->head;
    while (current) {
        printf("%s(%d) -> ", current->data, current->frequency);
        current = current->next;
    }
    printf("NULL\n");
}

// Boolean to check if a given string is in the list/not. 
bool soll_isin(soll* s, char* str, long* cnt) {
    Node* node = find_node(s, str, cnt);
    if (!node) {
        return false;
    }
    switch (s->type) {
        case none:
            break;
        case mtf:
            move_to_front(s, node);
            break;
        case transpose:
            transpose_node(s, node);
            break;
        default:
            return false;
    }
    return true;
}


// TODO : Implement soll_tostring, convert list to a string representation.



// TODO : Implement soll_size, return size of the list.


// Function to get number of times element accessed. 
int soll_freq(soll* s, char* str) {
    if (!s || !str) return 0;

    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            return current->frequency;
        }
        current = current->next;
    }
    return 0;
}


//TODO : Modify the soll_isin function to re-organise the list when element is accessed depending on the orgtype.
