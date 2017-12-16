#include <stdbool.h>
#include "algorithms.h"


#define LEFT_CHILD(x) (2*(x)+1)
#define RIGHT_CHILD(x) (2*(x)+2)
#define PARENT(x) (((x)-1) / 2)


void heapsort(int array[], size_t n) {
    heapify(array, n);
    while (n > 0) {
        heap_delete(array, n--);
    }
}


void heapify(int array[], size_t n) {
    for (int i = PARENT(n-1); i >= 0; i--) {
        size_t k = i;
        int v = array[k];
        bool heap = false;
        while (!heap && LEFT_CHILD(k) < n) {
            size_t j = LEFT_CHILD(k);
            if (j < n-1) {
                if (array[j] < array[j+1]) {
                    j++;
                }
            }
            if (v >= array[j]) {
                heap = true;
            } else {
                array[k] = array[j];
                k = j;
            }
        }
        array[k] = v;
    }
}


/* Swap the maximum element of the heap to the end and fix the heap to maintain the invariant. */
void heap_delete(int heap[], size_t n) {
    swap(heap, 0, --n);
    size_t index = 0;
    while (LEFT_CHILD(index) < n) {
        size_t j = LEFT_CHILD(index);
        if (j + 1 < n && heap[LEFT_CHILD(index)] < heap[RIGHT_CHILD(index)]) {
            j++;
        }
        if (heap[index] >= heap[j]) {
            break;
        } else {
            swap(heap, index, j);
            index = j;
        }
    }
}


int ch06_tests() {
    puts("\n=== CHAPTER 6 TESTS ===");
    int tests_failed = 0;

    /* HEAPSORT */
    puts("Testing heapsort");
    ASSERT(test_sorting_f(heapsort) == 0);

    return tests_failed;
}
