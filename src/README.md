# Functions:

**`cpuinfo_manip.c`**

Implementation of CPU monitoring features:

1. **CPU Information**:
   - Parses `/proc/cpuinfo` to get:
     - Model name (from 'model name' field)
     - Core count (from 'cpu cores' field)
     - Thread count (from 'siblings' field)

2. **CPU Usage Calculation**:
   - Reads `/proc/stat` for CPU time measurements
   - Implements usage algorithm:
     ```c
     usage = (total_time - idle_time) / total_time * 100
     ```
   - Maintains state between calls for delta calculations

**`meminfo_manip.c`**

Provides functionality to retrieve and format memory usage data from the Linux `/proc/meminfo` file.  
It exposes the following function:

- **`const char* get_memory_info();`**  
  Returns a static string containing:
  - Total physical memory (in MB)
  - Physical memory usage (percentage)
  - Total swap memory (in MB)
  - Swap memory usage (percentage)

  **Input Parameters:**  
  None

  **Return:**  
  A formatted `const char*` string.  
  Example output:
  Total physical memory: 11861 MB | Usage: 19.48% | Total swap: 4095 MB | Usage: 0.00%

  **Macro:**  
    `#define MEMINFO_STR_LEN 256`  
    Specifies the maximum length of the returned memory information string.

    
**`tui.c`**

This module provides a basic Text User Interface (TUI) abstraction layer using the `ncurses` library. It simplifies screen initialization, cleanup, drawing text, handling basic input, and managing coordinates.

**TUI Initialization and Control Functions:**

* **`void ui_init(void);`**
    * Initializes the `ncurses` environment.
    * Sets up the terminal for TUI operations (cbreak mode, no echo, hidden cursor, keypad enabled).

* **`void ui_cleanup(void);`**
    * Restores the terminal to its original state before the program exits.

* **`void ui_clear(void);`**
    * Clears the internal screen buffer. Does not update the physical display.

* **`void ui_refresh(void);`**
    * Updates the physical terminal screen with the current content of the buffer.

* **`void ui_set_nodelay(bool enabled);`**
    * Sets the input mode.
    * **Input:** `enabled` (boolean): `true` for non-blocking input, `false` for blocking input.

* **`int ui_exit(void);`**
    * Checks for user input to exit the TUI.
    * **Return:** `1` if 'q' or 'Q' is pressed, `0` otherwise. Note: Behavior depends on whether non-blocking mode is set.

* **`void ui_get_dims(int *rows, int *cols);`**
    * Retrieves the current dimensions (height and width) of the terminal window.
    * **Output:** `rows`, `cols` (pointers to integers): These will be filled with the terminal dimensions.

**Coordinate System Helper Functions:**

* **`tui_coord_t tui_get_relative_coord(float row_ratio, float col_ratio);`**
    * Calculates absolute terminal coordinates based on relative percentages (0.0 to 1.0) of the screen dimensions.
    * **Input:** `row_ratio` (vertical percentage), `col_ratio` (horizontal percentage).
    * **Return:** A `tui_coord_t` structure containing the calculated `row` and `col`.

* **`tui_coord_t tui_clamp_coord(tui_coord_t coord);`**
    * Ensures that a given coordinate falls within the valid boundaries of the terminal screen.
    * **Input:** `coord` (The `tui_coord_t` to check).
    * **Return:** A `tui_coord_t` structure with `row` and `col` adjusted to be within bounds.

* **`void tui_draw_text(tui_coord_t pt, const char *text);`**
    * Draws the given text string at the specified coordinate.
    * It automatically clamps the coordinates before drawing to prevent errors.
    * **Input:** `pt` (The `tui_coord_t` for drawing), `text` (The string to display).
