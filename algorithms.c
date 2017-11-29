#include "algorithms.h"


/* Sort the elements of `array` in place.
 *
 *   Idea: Find the smallest number and swap it with the first element. Find the second smallest
 *   number and swap it with the second element, and so on until the list is sorted.
 *
 *   Time analysis: The outer loop runs n times, so n swaps are made. When i=0, the inner loop
 *   runs n-1 times, when i=1 n-2 times, and so on for a total of n-1 + n-2 + ... + 1 times,
 *   which is equal to n(n-1)/2. This is asymptotically equivalent to n^2, so O(n^2) comparisons
 *   are made. Therefore the overall time complexity is O(n^2).
 *
 *   Space analysis: No extra space is used, so O(1).
 */
void selection_sort(int array[], size_t n) {
    /* On each run of this loop, the smallest number in array[i...n] is found and swapped with
     * array[i].
     */
    for (size_t i = 0; i < n; i++) {
        int minimum = array[i];
        size_t minimum_pos = i;
        /* This loop finds the smallest number in array[i...n]. */
        for (size_t j = i+1; j < n; j++) {
            if (array[j] < minimum) {
                minimum = array[j];
                minimum_pos = j;
            }
        }
        swap(array, i, minimum_pos);
    }
}


void swap(int array[], size_t i, size_t j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


void run_tests(void) {
    return;
}


int main(int argc, char* argv[]) {
    run_tests();
    return 0;
}
