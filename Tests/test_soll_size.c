#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../soll.h"
#include "../Linked/specific.h"


void test_soll_size(void);
void test_soll_size_edgecases(void);

int main() {
    test_soll_size();
    test_soll_size_edgecases();
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

void test_soll_size_edgecases(void){
    soll* s = soll_init(none);

    // Initial size should be 0.
    assert(soll_size(s) == 0);
    printf("Initial size zero passed.\n");

    // Add one element, then remove it.
    soll_add(s, "test1");
    soll_remove(s, "test1");
    assert(soll_size(s) == 0);
    printf("Add and remove one element passed.\n");

    // Add the same element multiple times.
    soll_add(s, "test1");
    soll_add(s, "test1");
    assert(soll_size(s) == 1);
    printf("Duplicate add w/o size increase passed.\n");

    // Remove non-existent element.
    soll_remove(s, "nonexistent");
    assert(soll_size(s) == 1);
    printf("Remove non-existent element passed.\n");

    // Re-add after removal.
    soll_remove(s, "test1");
    soll_add(s, "test1");
    assert(soll_size(s) == 1);
    printf("Re-add after removal passed.\n");

    // Add multiple  elements.
    soll_add(s, "test2");
    soll_add(s, "test3");
    assert(soll_size(s) == 3);
    printf("Multiple additions passed.\n");

    // Remove all, check size.
    soll_remove(s, "test1");
    soll_remove(s, "test2");
    soll_remove(s, "test3");
    assert(soll_size(s) == 0);
    printf("Remove all elements passed.\n");

    soll_free(s);
    printf("All edge cases passed.\n");
}
