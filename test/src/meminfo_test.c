/**
 * @file meminfo_test.c
 * @brief Test suite for the meminfo_manip library.
 *
 * This file tests the function that retrieves system memory information
 * to ensure that the output is valid and correctly formatted.
 * Uses assert.h for basic validation checks.
 *
 * @author Alex
 * @version 1.0
 * @date 2025
 */

#include <assert.h>
#include "../../src/meminfo_manip.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char* info = get_memory_info();

    printf("Memory Info Output: %s\n", info);

    // Automatic tests
    // Check if the output string is not NULL and has a reasonable length
    assert(info != NULL);
    assert(strlen(info) > 0); 
    assert(strstr(info, "MB") != NULL);
    assert(strstr(info, "Usage") != NULL || strstr(info, "Uso") != NULL); // Check for "Usage"

    printf("All tests passed.\n");

    return 0;
}
