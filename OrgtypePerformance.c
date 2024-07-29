#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "soll.h" 


typedef struct {
    double add_time;
    double search_time;
    double remove_time;
    double total_time;
    char name[20];
} PerformanceStats;

double test_orgtype_performance(char* org_type, int list_size);
double measure_performance(soll* s, int list_size);
orgtype get_orgtype_from_string(const char* org_type_str);
PerformanceStats simulate_operations(soll* s, int initial_size);
int compare(const void* a, const void* b);


int main() {
    unsigned int list_size;
    int status;

    do {
        printf("What size list do you wish to test? (1-10000): ");
        status = scanf("%u", &list_size);
        
        // Clearing the input buffer.
        while (getchar() != '\n');

        if (status != 1 || list_size < 1 || list_size > 10000) {
            printf("Sorry, that's not possible. Please input an integer in the range 1-10000\n");
        }
    } while (status != 1 || list_size < 1 || list_size > 10000);

    char* org_types[] = {"none", "mtf", "transpose"};
    PerformanceStats stats[3];

    for (int i = 0; i < 3; i++) {
        soll* s = soll_init(get_orgtype_from_string(org_types[i]));
        stats[i] = simulate_operations(s, list_size);
        strcpy(stats[i].name, org_types[i]);
        soll_free(s);
    }

    // Sort results by total time.
    qsort(stats, 3, sizeof(PerformanceStats), compare);

    // Display ordered results.
    printf("Add Time    : ");
    for (int i = 0; i < 3; i++) {
        printf("(%s) %.6f s | ", stats[i].name, stats[i].add_time);
    }
    printf("\nSearch Time : ");
    for (int i = 0; i < 3; i++) {
        printf("(%s) %.6f s | ", stats[i].name, stats[i].search_time);
    }
    printf("\nRemove Time : ");
    for (int i = 0; i < 3; i++) {
        printf("(%s) %.6f s | ", stats[i].name, stats[i].remove_time);
    }
    printf("\nTotal Time  : ");
    for (int i = 0; i < 3; i++) {
        printf("(%s) %.6f s | ", stats[i].name, stats[i].total_time);
    }
    printf("\n");

    return 0;
}

orgtype get_orgtype_from_string(const char* org_type_str) {
    if (strcmp(org_type_str, "none") == 0) return none;
      else if (strcmp(org_type_str, "mtf") == 0) return mtf;
      else if (strcmp(org_type_str, "transpose") == 0) return transpose;
    return none;
}

PerformanceStats simulate_operations(soll* s, int initial_size) {
    clock_t start, end;
    PerformanceStats stats = {0.0, 0.0, 0.0, 0.0, ""};
    char str[20];

    // Simulate adding.
    start = clock();
    for (int i = 0; i < initial_size; i++) {
        snprintf(str, sizeof(str), "item%d", i);
        soll_add(s, str);
    }
    end = clock();
    stats.add_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Simulate searching.
    start = clock();
    for (int i = 0; i < initial_size * 10; i++) {
        snprintf(str, sizeof(str), "item%d", rand() % initial_size);
        long cnt = 0;
        soll_isin(s, str, &cnt);
    }
    end = clock();
    stats.search_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Simulate removing.
    start = clock();
    for (int i = 0; i < initial_size / 2; i++) {
        snprintf(str, sizeof(str), "item%d", rand() % initial_size);
        soll_remove(s, str);
    }
    end = clock();
    stats.remove_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Calculate  total time spent for all operations.
    stats.total_time = stats.add_time + stats.search_time + stats.remove_time;

    return stats;
}

// Compare the performance stats so they can be displayed in descending order.
int compare(const void* a, const void* b) {
    PerformanceStats *statsA = (PerformanceStats *)a;
    PerformanceStats *statsB = (PerformanceStats *)b;

    return (statsA->total_time > statsB->total_time) - (statsA->total_time < statsB->total_time);
}
