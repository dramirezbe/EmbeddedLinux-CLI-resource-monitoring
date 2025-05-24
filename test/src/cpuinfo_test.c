/**
 * @file cpuinfo_test.c
 * @author Carlos
 * @brief Here an explanation
 */


#include <assert.h>
#include "../../src/cpuinfo_manip.h"


#include <stdio.h>          // For printf
#include <assert.h>        // For assertions
#include <time.h>
#include <stdlib.h>
#include <unistd.h>



// Test function for CPU information
void test_cpu_info() {
    CPUInfo cpu;  // Create CPU info structure
    get_cpu_info(&cpu);  // Get CPU information
    
    printf("=== Test get_cpu_info() ===\n");
    printf("Name: %s\n", cpu.name);  // Print CPU name
    printf("Cores: %d\n", cpu.cores); // Print core count
    printf("Threads: %d\n", cpu.threads);  // Print thread count
    
    // Verify core count is positive
    assert(cpu.cores > 0);
    // Verify thread count >= core count
    assert(cpu.threads >= cpu.cores);
    printf("Test get_cpu_info() passed!\n\n");
}

// Test function for CPU usage calculation
void test_cpu_usage() {
    CPUInfo cpu;  // Create CPU info structure
    get_cpu_info(&cpu);  // Get static CPU info
    
    printf("=== Test get_cpu_usage() ===\n");
    
    // First measurement
    get_cpu_usage(&cpu);
    printf("Fist call: %.2f%%\n", cpu.usage);
    
    // Second measurement after 1 second
    sleep(1);
    get_cpu_usage(&cpu);
    printf("Second call: %.2f%%\n", cpu.usage);
    
    // Verify usage is between 0% and 100%
    assert(cpu.usage >= 0.0 && cpu.usage <= 100.0);
    printf("Test get_cpu_usage() passed!\n\n");
}

int main() {
    test_cpu_info();    // Run CPU info test
    test_cpu_usage();   // Run CPU usage test
    return 0;
}
