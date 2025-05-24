/**
 * @file cpuinfo_manip.c
 * @author Carlos
 * @brief Implementation file for CPU information and usage manipulation.
 * Provides functions to read /proc/cpuinfo and /proc/stat
 * to determine CPU specs and calculate real-time usage.
 */

#include "cpuinfo_manip.h" // Include our header file
#include <stdio.h>         // For file operations and printf
#include <stdlib.h>        // For exit()
#include <string.h>        // For string operations
#include <unistd.h>        // For sleep()
#include <ctype.h>         // For isdigit()

// Get static CPU information from /proc/cpuinfo
void get_cpu_info(CPUInfo *cpu) {
    // Initialize CPUInfo members to ensure sane defaults
    cpu->name[0] = '\0';
    cpu->cores = 0;
    cpu->threads = 0;
    // cpu->usage and cpu->thread_usage are populated by get_cpu_usage()

    FILE *file = fopen("/proc/cpuinfo", "r"); // Open cpuinfo file
    if (file == NULL) { // Check if file opened successfully
        perror("Error opening /proc/cpuinfo"); // Print error
        // For a library function, returning an error status is generally preferred over exit().
        // However, if this info is critical for the TUI, exiting might be the intended behavior.
        exit(EXIT_FAILURE); 
    }

    char line[256];     // Buffer for reading lines
    int processor_entries = 0; // Count of "processor" lines (total logical processors)
    int model_name_found = 0;
    int cpu_cores_found = 0;
    int siblings_found = 0;

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        // Trim leading spaces for easier parsing
        char *trimmed_line = line;
        while (*trimmed_line && isspace((unsigned char)*trimmed_line)) {
            trimmed_line++;
        }

        // Parse model name (typically found once per CPU type)
        if (!model_name_found && strncmp(trimmed_line, "model name", 10) == 0) {
            // Extract model name after colon and trim leading spaces
            char *colon = strchr(trimmed_line, ':');
            if (colon) {
                char *model = colon + 1;
                while (*model && isspace((unsigned char)*model)) {
                    model++;
                }
                // Remove trailing newline if present
                size_t len = strlen(model);
                if (len > 0 && model[len - 1] == '\n') {
                    model[len - 1] = '\0';
                }
                strncpy(cpu->name, model, MAX_NAME_LENGTH - 1);
                cpu->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
                model_name_found = 1;
            }
        // Parse CPU cores (physical cores per package, typically found once)
        } else if (!cpu_cores_found && strncmp(trimmed_line, "cpu cores", 9) == 0) {
            if (sscanf(trimmed_line, "%*[^:]:%d", &cpu->cores) == 1) {
                cpu_cores_found = 1;
            }
        // Parse siblings (logical processors per package, typically found once)
        } else if (!siblings_found && strncmp(trimmed_line, "siblings", 8) == 0) {
            if (sscanf(trimmed_line, "%*[^:]:%d", &cpu->threads) == 1) {
                siblings_found = 1;
            }
        // Count total logical processors
        } else if (strncmp(trimmed_line, "processor", 9) == 0) {
            processor_entries++;
        }

        // Model name, cores, and siblings are usually consistent across all processor entries
        // for the same physical package. We can break after finding them once.
        if (model_name_found && cpu_cores_found && siblings_found) {
           break;
        }
    }

    // Fallback logic if specific fields weren't found or parsed successfully.
    // If 'siblings' (logical processors per package) was not found.
    if (!siblings_found || cpu->threads == 0) {
        cpu->threads = processor_entries; // Fallback to total 'processor' entries.
    }

    // If 'cpu cores' (physical cores per package) was not found.
    if (!cpu_cores_found || cpu->cores == 0) {
        // This is a rough guess. If 'cpu cores' is missing, accurately determining
        // physical cores is difficult. Assuming threads count (from siblings or processor_entries)
        // might be incorrect if SMT is active (e.g., cores = threads / 2).
        // Setting cores = threads assumes no SMT or that 'threads' somehow represents cores.
        // A safer minimum is 1.
        cpu->cores = cpu->threads > 0 ? cpu->threads : 1; // Highly speculative if threads > 1.
                                                          // A comment about this guess is important.
    }

    // Final sanity checks
    if (cpu->cores == 0) cpu->cores = 1;     // Ensure at least one core.
    if (cpu->threads == 0) cpu->threads = 1; // Ensure at least one thread.
    if (cpu->threads < cpu->cores) cpu->threads = cpu->cores; // Logical threads cannot be less than physical cores.

    fclose(file); // Close the file
}

// Initialize CPU stats structure array with zeros
void init_cpu_stats_array(CPUStats *stats, int count) {
    memset(stats, 0, sizeof(CPUStats) * count); // Zero out the structures
}

// Read current CPU statistics from /proc/stat for all CPUs
void read_cpu_stats_all(CPUStats *stats, int num_threads) {
    FILE *file = fopen("/proc/stat", "r"); // Open stat file
    if (file == NULL) {
        perror("Error opening /proc/stat");
        // Consider returning an error or setting a flag instead of exiting in a library function.
        exit(EXIT_FAILURE);
    }

    char line[256]; // Buffer for reading lines
    int cpu_index;
    int items_parsed;

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        // Parse the aggregate "cpu" line (must have a space after "cpu")
        if (strncmp(line, "cpu ", 4) == 0) {
            items_parsed = sscanf(line + 3, " %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", // Skip "cpu" and parse from space
                                  &stats[0].user, &stats[0].nice, &stats[0].system, &stats[0].idle,
                                  &stats[0].iowait, &stats[0].irq, &stats[0].softirq, &stats[0].steal,
                                  &stats[0].guest, &stats[0].guest_nice);
            if (items_parsed != 10) {
                // Log error or handle incomplete parse for aggregate CPU line
                fprintf(stderr, "Warning: Failed to parse aggregate CPU line in /proc/stat\n");
            }
        // Parse individual CPU lines "cpuX ..."
        } else if (sscanf(line, "cpu%d ", &cpu_index) == 1) {
            if (cpu_index < num_threads) {
                // The format string for sscanf needs to capture the numbers after "cpu%d "
                // Adjust pointer to start scanning after "cpu%d " part.
                char* p = line;
                while (*p && !isspace(*p)) p++; // Move past "cpu%d"
                while (*p && isspace(*p)) p++;  // Move past spaces

                items_parsed = sscanf(p, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                                      &stats[cpu_index + 1].user, &stats[cpu_index + 1].nice,
                                      &stats[cpu_index + 1].system, &stats[cpu_index + 1].idle,
                                      &stats[cpu_index + 1].iowait, &stats[cpu_index + 1].irq,
                                      &stats[cpu_index + 1].softirq, &stats[cpu_index + 1].steal,
                                      &stats[cpu_index + 1].guest, &stats[cpu_index + 1].guest_nice);
                if (items_parsed != 10) {
                    // Log error or handle incomplete parse for individual CPU line
                    fprintf(stderr, "Warning: Failed to parse CPU%d line in /proc/stat\n", cpu_index);
                }
            }
        } else if (strncmp(line, "cpu", 3) != 0) {
            // If we've read past all 'cpu' lines, we can stop.
            break;
        }
    }

    fclose(file); // Close the file
}

// Calculate CPU usage percentage between two measurements
double calculate_cpu_usage(const CPUStats *prev, const CPUStats *curr) {
    // Calculate idle and non-idle times for previous measurement
    unsigned long prev_idle = prev->idle + prev->iowait;
    unsigned long prev_non_idle = prev->user + prev->nice + prev->system +
                                  prev->irq + prev->softirq + prev->steal;

    // Calculate idle and non-idle times for current measurement
    unsigned long idle = curr->idle + curr->iowait;
    unsigned long non_idle = curr->user + curr->nice + curr->system +
                             curr->irq + curr->softirq + curr->steal;

    // Calculate total times
    unsigned long prev_total = prev_idle + prev_non_idle;
    unsigned long total = idle + non_idle;

    // Calculate differences between measurements
    unsigned long total_diff = total - prev_total;
    unsigned long idle_diff = idle - prev_idle;

    if (total_diff == 0) return 0.0; // Prevent division by zero

    // Calculate usage percentage: (total - idle) / total
    return (double)(total_diff - idle_diff) * 100.0 / total_diff;
}

// Get current CPU usage percentage (aggregate and per-thread)
void get_cpu_usage(CPUInfo *cpu) {
    static CPUStats prev_stats[MAX_CPUS + 1], curr_stats[MAX_CPUS + 1]; // Persistent between calls
    static int first_run = 1; // Flag for first run
    int num_threads = cpu->threads;

    if (first_run) { // Initialize on first run
        init_cpu_stats_array(prev_stats, num_threads + 1); // Zero out previous stats
        read_cpu_stats_all(prev_stats, num_threads);       // Take initial measurement
        first_run = 0;                                     // Clear flag
        sleep(1);                                          // Wait before next measurement for accurate delta
    }

    read_cpu_stats_all(curr_stats, num_threads); // Take current measurement

    // Calculate aggregate usage
    // Store aggregate usage in cpu->usage (as per previous convention, though cpu->usage was a single double)
    // If cpu->usage is meant for the array, it would be cpu->usage[0]
    cpu->usage = calculate_cpu_usage(&prev_stats[0], &curr_stats[0]); // This matches CPUInfo.usage

    // Calculate usage for each thread
    for (int i = 0; i < num_threads; i++) {
        cpu->thread_usage[i] = calculate_cpu_usage(&prev_stats[i + 1], &curr_stats[i + 1]);
    }

    // Current becomes previous for next call
    memcpy(prev_stats, curr_stats, sizeof(CPUStats) * (num_threads + 1));
}