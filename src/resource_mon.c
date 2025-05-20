/**
 * @file resource_mon.c
 * @author David, Leandro
 * @brief Here an explanation
 */

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"
#include "tui.h"

int main(int argc, char *argv[]) {

    ui_init();
    ui_set_nodelay(true);

    while (1) {
        // Exit the loop if the user presses 'q'
        if (ui_exit())
            break;

        ui_clear();

        display_ax_t cpu_ax = {.x = 0.20f, .y = 0.15f};
        display_ax_t mem_ax = {.x = 0.20f, .y = 0.45f};

        // Calculate positions using relative coordinates (values between 0.0 and 1.0)
        // For example, 20% down and 15% across for CPU info; 20% down and 45% across for memory info.
        tui_coord_t cpu_coord = tui_get_relative_coord(cpu_ax.x, cpu_ax.y);
        tui_coord_t mem_coord = tui_get_relative_coord(mem_ax.x, mem_ax.y);

        // Display static information. Later, you can integrate dynamic CPU and memory data.
        tui_draw_text(cpu_coord, "CPU: info here");
        tui_draw_text(mem_coord, "Mem: info here");

        ui_refresh();
        sleep(1);
    }

    ui_cleanup();
    return 0;
}
