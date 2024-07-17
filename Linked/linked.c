#include "specific.h"
#include "soll.h"

// TODO : create node function



// TODO : Implement soll_init, initialise the list.



// TODO : Implement soll_add, add element to the list. 



// TODO : Implement soll_remove, remove element from the list.



// TODO : Implement soll_isin, check if element is in list + increment its frequency.



// TODO : Implement soll_tostring, convert list to a string representation.



// TODO : Implement soll_size, return size of the list.



// TODO : Implement soll_free, free the allocated memory.



// TODO : Implement soll_freq, return the frequency of an element. 



// TODO : Implement move_to_front function.



// TODO : Implement transpose function.



//TODO : Modify the soll_isin function to re-organise the list when element is accessed depending on the orgtype.

// Function to get the orgtype and convert it to a string. 
const char* SOLLTYPE = SOLLTYPE_NONE;

const char* get_solltype_name(orgtype type) {
    switch (type) {
        case none:
            SOLLTYPE = SOLLTYPE_NONE;
            return SOLLTYPE_NONE;
        case mtf:
            SOLLTYPE = SOLLTYPE_MTF;
            return SOLLTYPE_MTF;
        case transpose:
            SOLLTYPE = SOLLTYPE_TRANSPOSE;
            return SOLLTYPE_TRANSPOSE;
        default:
            SOLLTYPE = "unknown";
            return "unknown";
    }
}

