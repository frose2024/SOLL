#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "soll.h"
#include "../Linked/specific.h"


void test_soll_size(void);

int main() {
    test_soll_size();
    return 0;
}

void test_soll_size(void) {
    soll* s = soll_init(none);

    assert(soll_size(s) == 0);

    soll_add(s, "test1");
    assert(soll_size(s) == 1);

    soll_add(s, "test2");
    soll_add(s, "test3");
    assert(soll_size(s) == 3);

    soll_remove(s, "test2");
    assert(soll_size(s) == 2);

    soll_free(s);
    printf("soll_size passed.\n");
}
