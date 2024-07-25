#include "specific.h"

static const char* current_solltype = "none";

const char* get_solltype(void) {
    return current_solltype;
}

void set_solltype(orgtype type) {
    static const char* types[] = {"none", "mtf", "transpose", "unknown"};
    current_solltype = types[type];
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
    soll* s = (soll*)malloc(sizeof(soll));
    if (!s) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    s->type = type;

    set_solltype(type);
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
    new_node->data = strdup(str);                               
    if (!new_node->data) {
        fprintf(stderr, "Memory allocation failed\n");          
        free(new_node);
        exit(EXIT_FAILURE);                                    
    }
    new_node->next = NULL;                                      
    new_node->prev = NULL;                                      
    new_node->frequency = 1;                                   
    return new_node;                                         
}                       

// soll_add - add element to the list.
void soll_add(soll* s, char* str) {
    if (!s) {
        return;
    }
    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            current->frequency++;
            return;
        }
        current = current->next;
    }
    Node* new_node = create_node(str);
    if (!new_node) {
        return;
    }
    if (!s->head) {
        s->head = s->tail = new_node;
    } else {
        s->tail->next = new_node;
        new_node->prev = s->tail;
        s->tail = new_node;
    }
    s->size++;
    assert_list_integrity(s);
}

//  soll_free - free allocated memory.
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

//  soll_remove - remove element from the list.
bool soll_remove(soll* s, char* str) {
    if (!s || !str) {
        return false;
    }
    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                s->head = current->next;
                if (s->head) {
                    s->head->prev = NULL;
                }
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
    assert_list_integrity(s);
    return false;
}

// Hhelper function - find node + count the pointer chases. 
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

// Function to apply MTF orgtype.
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

// Function to apply transpose orgtype.
void transpose_node(soll* s, Node* node) {
    if (node == s->head || !node->prev) {
        return;
    }
    Node* prev = node->prev;
    Node* prevprev = prev->prev;
    Node* next = node->next;

    if (next) {
        next->prev = prev;
    } else {
        s->tail = prev;
    }
    prev->next = next;

    node->next = prev;
    node->prev = prevprev;
    prev->prev = node;
    if (prevprev) {
        prevprev->next = node;
    } else {
        s->head = node;
    }
}

// Print list when debugging.
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

// Function to turn list into a string.
void soll_tostring(soll* s, char* str) {
    if (!s || !s->head) {
        strcpy(str, "");
        return;
    }
    Node* current = s->head;
    char* end = str + 999;
    str[0] = '\0';
    char* ptr = str;

    while (current && ptr < end) {
        ptr += snprintf(ptr, end - ptr, "%s(%d)", current->data, current->frequency);
        if (current->next && ptr < end) {
            ptr += snprintf(ptr, end - ptr, "|");
        }
        current = current->next;
    }
    *ptr = '\0';
}

// soll_size - return size of the list.
int soll_size(soll* s) {
    if (s == NULL) {
        return 0;
    }
    return s->size;
}

// soll_freq - number of times element accessed. 
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

// Helper function to check pointers are attaching/de-attaching correctly.
void assert_list_integrity(soll* s) {
    if (!s || !s->head) return;
    Node* current = s->head;
    assert(current->prev == NULL);
    while (current) {
        if (current->next) {
            assert(current->next->prev == current);
        } else {
            assert(s->tail == current);
        }
        current = current->next;
    }
}
