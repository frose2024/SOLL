#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../Linked/specific.h"
#include "soll.h"


void test_soll_tostring(void);
void print_list_test(soll* s);

int main() {
    test_soll_tostring();
    return 0;
}

void print_list_test(soll* s) {
    Node* current = s->head;
    while (current) {
        printf("%s(%d) -> ", current->data, current->frequency);
        current = current->next;
    }
    printf("NULL\n");
}

void test_soll_tostring(void) {
    soll* s = soll_init(none);
    char result[1000];

    soll_tostring(s, result);
    assert(strcmp(result, "") == 0);
    assert_list_integrity(s);

    soll_add(s, "1one");
    assert_list_integrity(s);
    soll_add(s, "2two");
    assert_list_integrity(s);
    soll_add(s, "3three");
    assert_list_integrity(s);

    soll_tostring(s, result);
    assert(strcmp(result, "1one(1)|2two(1)|3three(1)") == 0);

    soll_add(s, "1one");
    assert_list_integrity(s);
    soll_add(s, "2two");
    assert_list_integrity(s);

    soll_tostring(s, result);
    assert(strcmp(result, "1one(2)|2two(2)|3three(1)") == 0);

    soll_remove(s, "2two");
    assert_list_integrity(s);
    soll_tostring(s, result);
    assert(strcmp(result, "1one(2)|3three(1)") == 0);

    soll_add(s, "4four");
    assert_list_integrity(s);
    soll_add(s, "5five");
    assert_list_integrity(s);
    soll_add(s, "2two");
    assert_list_integrity(s);

    soll_tostring(s, result);
    assert(strcmp(result, "1one(2)|3three(1)|4four(1)|5five(1)|2two(1)") == 0);

    long dummy_count;
    soll_isin(s, "2two", &dummy_count);
    assert_list_integrity(s);
    soll_isin(s, "2two", &dummy_count);
    assert_list_integrity(s);

    soll_tostring(s, result);
    assert(strcmp(result, "1one(2)|3three(1)|4four(1)|5five(1)|2two(3)") == 0);

    soll_free(s);
    printf("soll_tostring tests passed.\n");
}
