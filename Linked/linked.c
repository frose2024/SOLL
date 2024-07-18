#include "specific.h"



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
    return s;                                               
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
    // If list is empty, set head and tail to new node.                      
    if (!s->head) {                                             
        s->head = s->tail = new_node;   
        // If list is not empty, add new node to end of list.                             
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



// TODO : Implement soll_isin, check if element is in list + increment its frequency.



// TODO : Implement soll_tostring, convert list to a string representation.



// TODO : Implement soll_size, return size of the list.



// TODO : Implement soll_freq, return the frequency of an element. 



// TODO : Implement move_to_front function.



// TODO : Implement transpose function.



//TODO : Modify the soll_isin function to re-organise the list when element is accessed depending on the orgtype.
