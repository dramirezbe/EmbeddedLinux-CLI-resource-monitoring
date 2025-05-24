/**
 * @file cpuinfo_manip.h
 * @author Carlos
 * @brief Header for CPU Information and Usage Manipulation.
 *
 * Defines structures and declares functions to retrieve CPU hardware details
 * (model, cores, threads) from /proc/cpuinfo and to calculate real-time CPU
 * usage (aggregate and per-thread) by processing /proc/stat.
 */

#ifndef CPUINFO_MANIP_H // Header guard to prevent multiple inclusions
#define CPUINFO_MANIP_H

#define MAX_CPUS 32         // Maximum number of CPUs supported
#define MAX_NAME_LENGTH 128 // Maximum length for CPU name string

/**
 * @brief Stores raw CPU time statistics for a single CPU core or aggregate.
 *
 * These values are counters read from /proc/stat. The difference between
 * successive readings is used to calculate CPU usage.
 * All values are in units of USER_HZ (typically 1/100th of a second).
 */
typedef struct {
    unsigned long user;       /**< Normal processes executing in user mode. */
    unsigned long nice;       /**< Niced processes executing in user mode. */
    unsigned long system;     /**< Processes executing in kernel mode. */
    unsigned long idle;       /**< Twiddling thumbs. */
    unsigned long iowait;     /**< Waiting for I/O to complete. */
    unsigned long irq;        /**< Servicing interrupts. */
    unsigned long softirq;    /**< Servicing softirqs. */
    unsigned long steal;      /**< Stolen time (for virtual machines). */
    unsigned long guest;      /**< Running a virtual CPU for guest OS. */
    unsigned long guest_nice; /**< Running a niced guest virtual CPU. */
} CPUStats;

/**
 * @brief Consolidates static CPU information and dynamic usage statistics.
 */
typedef struct {
    char name[MAX_NAME_LENGTH]; /**< CPU model name, e.g., "Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz". */
    int cores;                  /**< Number of physical cores per CPU package. */
    int threads;                /**< Number of logical processors (threads) per CPU package (includes SMT). */
    double usage;               /**< Aggregate CPU usage percentage (0.0 to 100.0). */
    double thread_usage[MAX_CPUS]; /**< Usage percentage for each logical thread/CPU (0.0 to 100.0). Index corresponds to CPU number (e.g., thread_usage[0] for cpu0). */
    CPUStats thread_stats[MAX_CPUS + 1]; /**< Raw CPU statistics. Index 0 for aggregate ("cpu" line in /proc/stat), indices 1 to MAX_CPUS for individual logical CPUs (cpu0, cpu1, ...). Note: This field is populated by internal static arrays in get_cpu_usage and not directly exposed or necessarily kept up-to-date in the passed CPUInfo struct by current functions. It's more of a placeholder for potential future use or internal state if refactored. */
} CPUInfo;

// Public function declarations
void get_cpu_info(CPUInfo *cpu); /**< @brief Populates the CPUInfo struct with static CPU details from /proc/cpuinfo. This includes model name, core count, and thread count. */
void get_cpu_usage(CPUInfo *cpu); /**< @brief Calculates and updates the aggregate and per-thread CPU usage percentages in the CPUInfo struct. It reads /proc/stat, compares with previous readings, and computes the deltas. */
void init_cpu_stats_array(CPUStats *stats, int count); /**< @brief Initializes an array of CPUStats structures to zero. Helper function. */
void read_cpu_stats_all(CPUStats *stats, int num_threads); /**< @brief Reads current CPU time statistics from /proc/stat for the aggregate CPU and each logical thread. Stores results in the provided stats array. Index 0 is for aggregate, subsequent indices for cpu0, cpu1, etc. */
double calculate_cpu_usage(const CPUStats *prev, const CPUStats *curr); /**< @brief Calculates CPU usage percentage based on two CPUStats snapshots (previous and current). */

#endif // CPUINFO_MANIP_H