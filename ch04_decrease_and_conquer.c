#include <stdlib.h>
#include "algorithms.h"


/* Sort the elements of `array` in ascending order.
 *
 *   Idea: Recursively sort the first n-1 elements of the array, and then insert the last element
 *   into its proper position in the sorted array.
 *
 *   Time analysis: In the worst case (when the array is already sorted in descending order), the
 *   inner loop runs 1 + 2 + 3 + ... + n-1 times, so as with selection sort the time complexity is
 *   O(n^2).
 *
 *   Space analysis: O(1).
 */
void insertion_sort(int array[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        int v = array[i];
        size_t j = i-1;
        while (j >= 0 && array[j] > v) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = v;
    }
}


/* Return a position of `datum` in the sorted array, or -1 if `datum` is not present.
 *
 *   Idea: Consider the middle element. If the datum is smaller, then recursively consider the left
 *   half of the array. If the datum is larger, consider the right half.
 *
 *   Time analysis: Each iteration of the loop reduces the size of the array to be considered by
 *   half, so in the worst case the loop runs for the number of times that n can be divided by two.
 *   This number is within a constant of log n, so the time complexity is O(log n).
 *
 *   Space analysis: O(1).
 */
long long binary_search(int array[], size_t n, int datum) {
    size_t start = 0, end = n;
    while (start < end) {
        size_t mid = (end + start) / 2;
        int midval = array[mid];
        if (midval == datum) {
            return mid;
        } else if (midval < datum) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return -1;
}


int ch04_tests() {
    puts("\n=== CHAPTER 4 TESTS ===");
    int tests_failed = 0;

    /* INSERTION SORT */
    puts("Testing insertion sort");
    ASSERT(test_sorting_f(insertion_sort) == 0);

    /* BINARY SEARCH */
    puts("Testing binary search");
    int bs_data[] = {-7, 4, 8, 9, 17};
    ASSERT(binary_search(bs_data, 5, -7) == 0);
    ASSERT(binary_search(bs_data, 5, 4) == 1);
    ASSERT(binary_search(bs_data, 5, 8) == 2);
    ASSERT(binary_search(bs_data, 5, 9) == 3);
    ASSERT(binary_search(bs_data, 5, 17) == 4);
    ASSERT(binary_search(bs_data, 5, 42) == -1);

    return tests_failed;
}
