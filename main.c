#include <stdio.h>
#include "algorithms.h"


int main(int argc, char* argv[]) {
    puts("Running test suite");
    int tests_failed = 0;
    tests_failed += ch03_tests();
    tests_failed += ch04_tests();
    tests_failed += ch05_tests();
    tests_failed += ch06_tests();
    if (tests_failed > 0) {
        printf("\nFAILED %d test%s.\n", tests_failed, tests_failed == 1 ? "" : "s");
    } else {
        printf("\nPASSED all tests.\n");
    }
    return 0;
}
