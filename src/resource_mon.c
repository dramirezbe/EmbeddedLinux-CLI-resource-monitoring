/**
 * @file resource_mon.c
 * @author David, Leandro
 * @brief Main application file for resource monitoring TUI.
 * Initializes the TUI and displays CPU and Memory information
 * in a continuous loop, including per-thread CPU usage.
 */

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"
#include <string.h> // Para usar strtok and strncpy
#include "tui.h"     // Include the TUI header
#include <unistd.h> // For sleep()

int main() {

    ui_init();
    ui_set_nodelay(true);
    CPUInfo cpu; // Create CPU info structure
    get_cpu_info(&cpu); // Get static CPU information once

    // Buffer for formatting display strings
    char display_buffer[256];
    // Buffer for a copy of memory info string because strtok modifies it
    char meminfo_copy[MEMINFO_STR_LEN];
    int max_rows, max_cols; // Variables to store terminal dimensions

    get_cpu_usage(&cpu); // Prime the CPU stats (first call might return 0)

    while (1) {
        sleep(1); // Wait for 1 second for CPU usage delta calculation

        // Check for exit *after* sleeping but *before* processing
        if (ui_exit())
            break;

        get_cpu_usage(&cpu); // Update CPU usage (aggregate and per-thread)
        char* meminfo_original = get_memory_info(); // Get current memory info
        ui_get_dims(&max_rows, &max_cols); // *** CORRECTED: Get dimensions ***

        ui_clear();

        // --- CPU Information ---
        tui_coord_t current_pos = tui_get_relative_coord(0.05f, 0.05f);

        tui_draw_text(current_pos, "--- CPU Information ---");
        current_pos.row++;
        current_pos.row++;

        snprintf(display_buffer, sizeof(display_buffer), "Model: %s", cpu.name);
        tui_draw_text(current_pos, display_buffer);
        current_pos.row++;

        snprintf(display_buffer, sizeof(display_buffer), "Cores: %d", cpu.cores);
        tui_draw_text(current_pos, display_buffer);
        current_pos.row++;

        snprintf(display_buffer, sizeof(display_buffer), "Threads: %d", cpu.threads);
        tui_draw_text(current_pos, display_buffer);
        current_pos.row++;

        snprintf(display_buffer, sizeof(display_buffer), "Usage: %.2f%%", cpu.usage);
        tui_draw_text(current_pos, display_buffer);
        current_pos.row++;

        // --- Thread Usage ---
        current_pos.row += 2;
        tui_draw_text(current_pos, "--- Thread Usage ---");
        current_pos.row++;
        current_pos.row++;

        for (int i = 0; i < cpu.threads; i++) {
            // *** CORRECTED: Use max_rows for boundary check ***
            if (current_pos.row >= max_rows - 1) { // -1 leaves one line margin
                tui_draw_text(current_pos, "..."); // Indicate more threads exist
                break; // Stop drawing threads if we hit the bottom
            }
            snprintf(display_buffer, sizeof(display_buffer), "Thread %2d: %6.2f%%", i, cpu.thread_usage[i]);
            tui_draw_text(current_pos, display_buffer);
            current_pos.row++;
        }

        // --- Memory Information ---
        // Position memory info to the right (e.g., 50% across)
        tui_coord_t mem_pos = tui_get_relative_coord(0.05f, 0.50f);

        tui_draw_text(mem_pos, "--- Memory Information ---");
        mem_pos.row++;
        mem_pos.row++;

        strncpy(meminfo_copy, meminfo_original, MEMINFO_STR_LEN - 1);
        meminfo_copy[MEMINFO_STR_LEN - 1] = '\0';

        char *line = strtok(meminfo_copy, "\n");
        // *** CORRECTED: Use max_rows for boundary check ***
        while (line != NULL && mem_pos.row < max_rows - 1) {
            if (*line != '\0') {
                tui_draw_text(mem_pos, line);
                mem_pos.row++;
            }
            line = strtok(NULL, "\n");
        }

        ui_refresh(); // Update the screen
        // sleep(1); // Moved to the top of the loop
    }

    ui_cleanup();
    return 0;
}