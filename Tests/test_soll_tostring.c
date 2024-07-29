#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../Linked/specific.h"
#include "../soll.h"


void print_list_test(soll* s);
void test_soll_tostring(void);
void test_soll_tostring_edgecases(void);

int main() {
    test_soll_tostring();
    test_soll_tostring_edgecases();
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

void test_soll_tostring_edgecases(){
    soll* s = soll_init(none);
    char result[1000];

    // Test empty list
    soll_tostring(s, result);
    assert(strcmp(result, "") == 0);
    printf("Empty list passed.\n");

    // Add elements, then remove them all
    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");
    soll_tostring(s, result);
    assert(strcmp(result, "test1(1)|test2(1)|test3(1)") == 0);

    soll_remove(s, "test1");
    soll_remove(s, "test2");
    soll_remove(s, "test3");
    soll_tostring(s, result);
    assert(strcmp(result, "") == 0);
    printf("Add and removeAll passed.\n");

    // Add elements, test duplication and removal
    soll_add(s, "test1");
    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_remove(s, "test1");
    soll_tostring(s, result);
    assert(strcmp(result, "test2(1)") == 0);
    printf("Complex operation passed.\n");

    // Test string representation after doing stuff to it. 
    soll_add(s, "test1");
    soll_add(s, "test3");
    soll_tostring(s, result);
    assert(strcmp(result, "test2(1)|test1(1)|test3(1)") == 0);

    // Test behavior with special characters in strings
    soll_add(s, "special&*chars");
    soll_tostring(s, result);
    assert(strstr(result, "special&*chars(1)") != NULL);
    printf("Special characters passed.\n");

    soll_free(s);
    printf("soll_tostring edge cases tests passed.\n");
}
