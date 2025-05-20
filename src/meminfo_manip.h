/**
 * @file meminfo_manip.h
 * @brief Library to retrieve memory usage information from /proc/meminfo.
 *
 * This library provides a function to read the system's
 * physical and swap memory usage.
 * 
 * @author 
 * Alex
 * @version 1.1
 * @date 2025
 */

#ifndef MEMINFO_MANIP_H
#define MEMINFO_MANIP_H

/// Maximum length of the returned string with memory information
#define MEMINFO_STR_LEN 256

/**
 * @brief Retrieves the system memory information.
 *
 * This function reads the /proc/meminfo file and calculates:
 * - Total physical memory (MB)
 * - Physical memory usage percentage
 * - Total swap memory (MB)
 * - Swap memory usage percentage
 *
 * @return const char* Pointer to a static string with the formatted information.
 * 
 * @note Example return:
 *       "Total physical memory: 11861 MB | Usage: 19.48% | Total swap: 4095 MB | Usage: 0.00%"
 */
const char* get_memory_info();

#endif // MEMINFO_MANIP_H

