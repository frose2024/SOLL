#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "soll.h"
#include "../Linked/specific.h"


void test_soll_isin_none(void);
void test_soll_isin_mtf(void);
void test_soll_isin_transpose(void);
void test_soll_isin_transpose_large(void);

int main(void) {
    printf("Testing soll_isin...\n");

    test_soll_isin_none();
    test_soll_isin_mtf();
    test_soll_isin_transpose();
    test_soll_isin_transpose_large();

    printf("All tests for soll_isin passed.\n");
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

void test_soll_isin_none(void) {
    soll* s = soll_init(none);
    long cnt;

    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");

    assert(soll_isin(s, "test2", &cnt));
    assert(cnt == 2);
    assert(soll_freq(s, "test2") == 2);
    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test3") == 1);
    assert(!soll_isin(s, "test4", &cnt));

    printf("soll_isin_none passed.\n");
    soll_free(s);
}

void test_soll_isin_mtf(void) {
    soll* s = soll_init(mtf);
    long cnt;

    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");
    //print_list(s);
    assert(soll_isin(s, "test2", &cnt));
    assert(cnt == 2);
    assert(s->head != NULL && strcmp(s->head->data, "test2") == 0);
    assert(soll_freq(s, "test2") == 2);
    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test3") == 1);
    assert(!soll_isin(s, "test4", &cnt));
    //print_list(s);
    printf("soll_isin_mtf passed.\n");
    soll_free(s);
}

void test_soll_isin_transpose(void) {
    soll* s = soll_init(transpose);
    long cnt;

    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");
    soll_add(s, "test4");
    soll_add(s, "test5");
    //print_list(s);

    assert(soll_isin(s, "test3", &cnt));
    assert(cnt == 3);

    //print_list(s);
    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, "test3") == 0) {
            break;
        }
        current = current->next;
    }

    assert(current != NULL);
    assert(strcmp(current->data, "test3") == 0);
    assert(current->prev != NULL);
    assert(strcmp(current->prev->data, "test1") == 0);
    assert(current->next != NULL);
    assert(strcmp(current->next->data, "test2") == 0);

    assert(soll_freq(s, "test2") == 1);
    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test3") == 2);
    assert(soll_freq(s, "test4") == 1);
    assert(soll_freq(s, "test5") == 1);
    assert(!soll_isin(s, "test6", &cnt));

    printf("soll_isin_transpose passed.\n");
    soll_free(s);
}

void test_soll_isin_transpose_large(void) {
    soll* s = soll_init(transpose);
    long cnt;

    char item[10];
    for (int i = 1; i <= 25; i++) {
        sprintf(item, "test%d", i);
        soll_add(s, item);
    }
    //print_list(s);
    assert(soll_isin(s, "test15", &cnt));
    assert(cnt == 15);

    //print_list(s);
    Node* current = s->head;
    while (current) {
        if (strcmp(current->data, "test15") == 0) {
            break;
        }
        current = current->next;
    }
    assert(current != NULL);
    assert(current->next != NULL);
    assert(strcmp(current->next->data, "test14") == 0);

    printf("soll_isin_transpose_large passed.\n");
    soll_free(s);
}
