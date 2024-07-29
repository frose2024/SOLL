#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../soll.h"
#include "../Linked/specific.h"


void test_soll_functions(void);
void test_soll_functions_edgecases(void);

int main(void) {
    test_soll_functions();
    test_soll_functions_edgecases();
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

void test_soll_functions_edgecases(void){
    soll * s = soll_init(none);

    // Testing adding duplicate elements. 
    soll_add(s, "test1");
    soll_add(s, "test1");
    assert(s->size == 1);
    printf("Duplicate test passed.\n");

    // Test removing non-existent elements
    bool removed = soll_remove(s, "nonexistent");
    assert(!removed);
    assert(s->size == 1);
    printf("Removing non-existent element passed.\n");

    // Testing soll_isin on empty list. 
    soll* empty = soll_init(none);
    long cnt = 0;
    bool found = soll_isin(empty, "test1", &cnt);
    assert(!found);
    printf("Empty list test passed.\n");

    // Test multiple removes 
    soll_add(s, "test2");
    soll_remove(s, "test1");
    soll_remove(s, "test2");
    assert(s->size == 0);
    printf("Multiple removes test passed.\n");

    // Test freeing empty list
    soll_free(empty);
    printf("Freeing empty list passed.\n");

    soll_free(s);
    printf("All edge cases passed.\n");
}
