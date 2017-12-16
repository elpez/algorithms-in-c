#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"


void swap(int array[], size_t i, size_t j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


int* copy_array(int source[], size_t start, size_t end) {
    size_t n = end - start;
    int* ret = safe_malloc(n * sizeof *ret);
    for (size_t i = 0; i < n; i++) {
        ret[i] = source[start+i];
    }
    return ret;
}


void print_array(int array[], size_t n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void* safe_malloc(size_t size) {
    void* ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in malloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}


void* safe_calloc(size_t num, size_t size) {
    void* ret = calloc(num, size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in calloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}


void* safe_realloc(void* ptr, size_t size) {
    void* ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "MEMORY ERROR in realloc: exiting immediately.\n");
        exit(1);
    }
    return ret;
}
