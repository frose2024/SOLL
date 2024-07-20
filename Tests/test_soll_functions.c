#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "soll.h"
#include "../Linked/specific.h"



int main(void) {
    test_soll_functions();
    return 0;
}

void test_soll_functions(void) {
    // Test soll_init
    soll* s = soll_init(none);
    assert(s != NULL);
    assert(s->head == NULL);
    assert(s->tail == NULL);
    assert(s->size == 0);
    assert(s->type == none);
    printf("soll_init passed.\n");

    // Test soll_add
    soll_add(s, "test1");
    assert(s->size == 1);
    assert(s->head != NULL);
    assert(s->tail != NULL);
    assert(strcmp(s->head->data, "test1") == 0);
    assert(s->head->frequency == 1);

    soll_add(s, "test2");
    assert(s->size == 2);
    assert(s->tail != NULL);
    assert(strcmp(s->tail->data, "test2") == 0);
    assert(s->tail->frequency == 1);
    assert(s->head->next == s->tail);
    assert(s->tail->prev == s->head);
    printf("soll_add passed.\n");

    // Test soll_remove
    assert(soll_remove(s, "test1"));
    assert(s->size == 1);
    assert(strcmp(s->head->data, "test2") == 0);
    assert(soll_remove(s, "test2"));
    assert(s->size == 0);
    printf("soll_remove passed.\n");

    // Test soll_free
    soll_add(s, "test3");
    soll_add(s, "test4");
    assert(s->size == 2);
    assert(s->head != NULL);
    assert(s->tail != NULL);
    assert(soll_free(s));
    printf("soll_free passed.\n");

    s = NULL;

    s = soll_init(none);
    assert(s != NULL);
    assert(s->head == NULL);
    assert(s->tail == NULL);
    assert(s->size == 0);
    assert(s->type == none);
    printf("Reinitialise after soll_free passed.\n");

    // Clean up
    soll_free(s);
    printf("All tests passed.\n");
}

