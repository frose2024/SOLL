#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../soll.h"
#include "../Linked/specific.h"


void test_soll_freq(void);
void test_soll_freq_edgecases(void);

int main(void) {
    test_soll_freq();
    test_soll_freq_edgecases();
    return 0;
}

void test_soll_freq(void) {
    // Test soll_freq w/ none orgtype.
    soll* s = soll_init(none);
    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");

    // Check start frequencies.
    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test2") == 1);
    assert(soll_freq(s, "test3") == 1);

    // Access elements, increase frequency.
    long cnt;
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test2", &cnt);

    // Check new frequencies.
    assert(soll_freq(s, "test1") == 3);
    assert(soll_freq(s, "test2") == 2);
    assert(soll_freq(s, "test3") == 1);

    soll_free(s);

    // Test soll_freq w/ mtf orgtype.
    s = soll_init(mtf);
    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");
    
    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test2") == 1);
    assert(soll_freq(s, "test3") == 1);

    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test2", &cnt);

    assert(soll_freq(s, "test1") == 3);
    assert(soll_freq(s, "test2") == 2);
    assert(soll_freq(s, "test3") == 1);

    soll_free(s);

    // Test soll_freq w/ trans orgtype.
    s = soll_init(transpose);
    soll_add(s, "test1");
    soll_add(s, "test2");
    soll_add(s, "test3");

    assert(soll_freq(s, "test1") == 1);
    assert(soll_freq(s, "test2") == 1);
    assert(soll_freq(s, "test3") == 1);

    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test2", &cnt);

    assert(soll_freq(s, "test1") == 3);
    assert(soll_freq(s, "test2") == 2);
    assert(soll_freq(s, "test3") == 1);

    soll_free(s);

    printf("basic soll_freq tests passed.\n");


    // Testing edge cases for soll_freq

}

void test_soll_freq_edgecases(void) {
    long cnt;

    // Test soll_freq with empty list.
    soll* s = soll_init(none);
    assert(soll_freq(s, "nonexistent") == 0);

    // Add elements to list + test non-existent elements.
    soll_add(s, "test1");
    soll_add(s, "test2");
    assert(soll_freq(s, "nonexistent") == 0); 

    // Repetitive adds and removals.
    soll_add(s, "test3");
    soll_add(s, "test3");
    soll_remove(s, "test3");
    soll_add(s, "test3");  // Should reset the frequency to 1.
    assert(soll_freq(s, "test3") == 1);

    // Access elements to simulate a really popular node. 
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test1", &cnt);
    soll_isin(s, "test1", &cnt);
    assert(soll_freq(s, "test1") == 4);

    soll_free(s);
    printf("soll_freq_edgecases passed.\n");
}
