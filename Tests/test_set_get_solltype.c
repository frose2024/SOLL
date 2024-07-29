#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "soll.h"
#include "../Linked/specific.h"


void test_set_get_solltype(void);
void test_soll_getsolltype_invalid(void);

int main(void) {
    test_set_get_solltype();
    test_soll_getsolltype_invalid();
    return 0;
}

void test_set_get_solltype(void) {
    set_solltype(none);
    assert(strcmp(get_solltype(), SOLLTYPE_NONE) == 0);
    set_solltype(mtf);
    assert(strcmp(get_solltype(), SOLLTYPE_MTF) == 0);
    set_solltype(transpose);
    assert(strcmp(get_solltype(), SOLLTYPE_TRANSPOSE) == 0);

    printf("set_solltype and get_solltype passed.\n");

    assert(strcmp(get_solltype_name(none), SOLLTYPE_NONE) == 0);
    assert(strcmp(get_solltype_name(mtf), SOLLTYPE_MTF) == 0);
    assert(strcmp(get_solltype_name(transpose), SOLLTYPE_TRANSPOSE) == 0);
    assert(strcmp(get_solltype_name(-1), "unknown") == 0);

    printf("get_solltype_name passed.\n");
}

void test_soll_getsolltype_invalid(void) {
    set_solltype((orgtype)6969);
    assert(strcmp(get_solltype(), "unknown") == 0);
    printf("Invalid type handling test passed.\n");
}



