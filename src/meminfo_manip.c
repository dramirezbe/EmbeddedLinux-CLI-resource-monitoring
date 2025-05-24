/**
 * @file meminfo_manip.c
 * @brief Implementation of the memory information functions.
 *
 * This file reads memory data from /proc/meminfo and calculates
 * the total and used percentages of physical and swap memory.
 * It provides the implementation of the function declared in meminfo_manip.h.
 *
 * @author 
 * Alex
 * @version 1.1
 * @date 2025
 *
 */
#include "meminfo_manip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_memory_info() {
    static char info[MEMINFO_STR_LEN];
    FILE* file = fopen("/proc/meminfo", "r");
    if (!file) {
        snprintf(info, MEMINFO_STR_LEN, "Error al abrir /proc/meminfo");
        return info;
    }

    long mem_total_kb = 0, mem_free_kb = 0, buffers_kb = 0, cached_kb = 0;
    long swap_total_kb = 0, swap_free_kb = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %ld kB", &mem_total_kb) == 1) continue;
        if (sscanf(line, "MemFree: %ld kB", &mem_free_kb) == 1) continue;
        if (sscanf(line, "Buffers: %ld kB", &buffers_kb) == 1) continue;
        if (sscanf(line, "Cached: %ld kB", &cached_kb) == 1) continue;
        if (sscanf(line, "SwapTotal: %ld kB", &swap_total_kb) == 1) continue;
        if (sscanf(line, "SwapFree: %ld kB", &swap_free_kb) == 1) continue;
    }
    fclose(file);

    long mem_used_kb = mem_total_kb - mem_free_kb - buffers_kb - cached_kb;
    float mem_usage_percent = mem_total_kb ? (mem_used_kb * 100.0f / mem_total_kb) : 0.0f;

    long swap_used_kb = swap_total_kb - swap_free_kb;
    float swap_usage_percent = swap_total_kb ? (swap_used_kb * 100.0f / swap_total_kb) : 0.0f;

    snprintf(info, MEMINFO_STR_LEN,
             "Total physical memory: %ld MB \nUsage: %.2f%% \nTotal swap: %ld MB \nUsage: %.2f%%\n",
             mem_total_kb / 1024, mem_usage_percent,
             swap_total_kb / 1024, swap_usage_percent);

    return info;
}
