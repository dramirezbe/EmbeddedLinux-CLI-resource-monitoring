# Functions:

**`cpuinfo_manip.c`**

Here explanation

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

Here explanation

