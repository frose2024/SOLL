#include <stdio.h>
#include <assert.h>
#include "soll.h"
#include "Linked/specific.h"

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
        printf("Testing soll_free...\n");
        soll_add(s, "test3");
        soll_add(s, "test4");
        assert(s->size == 2);
        assert(s->head != NULL);
        assert(s->tail != NULL);
        assert(soll_free(s));
    printf("soll_free passed.\n");

        s = NULL;

    //  Reinitialise, check if reinitalisation works after free
        s = soll_init(none);
        assert(s != NULL);
        assert(s->head == NULL);
        assert(s->tail == NULL);
        assert(s->size == 0);
        assert(s->type == none);
    printf("Reinitialization after soll_free passed.\n");




// Want to write tests for a bigger list, say 500 and 1000 items. 

    // Clean up
    soll_free(s);
    printf("All tests passed.\n");
}

/*Day 2, made tests for above functions. Talk about how they work (just assert tests really). Say
that I wanted to print out the lists to vosually confirm that they were being added to correctly
but realised I need to complete the tostring function firs.t  */

int main(void) {
    test_soll_functions();
    return 0;
}
