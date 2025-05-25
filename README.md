# EmbeddedLinux-CLI-resource-monitoring

This project consist in a system resource minotoring interface in Command Line Interface of Linux machines.

# Authors

- Leandro Zapata Marin lezapatam@unal.edu.co  CC:1002653862

- Yonnier Alexander Muñoz Salazar yomunozs@unal.edu.co

- Carlos Andres Cardona Cardona cacardonaca@unal.edu.co  Cc: 1053796695

- David Ramírez Betancourth dramirezbe@unal.edu.co CC: 1002636667

# Install

Install ncurses in your Linux System

```bash
sudo apt install build-essential libncurses5-dev libncursesw5-dev
```



# Main Program: `resource_mon.c`

This is the main application file for a real-time resource monitoring TUI (Text User Interface).

The program displays CPU and Memory information in a continuous loop with a terminal-based interface.

### Core Functionality:

1. **TUI Initialization**
   - Initializes the terminal user interface
   - Sets up non-blocking input for exit detection

2. **CPU Monitoring**
   - Displays CPU model, core count, and thread count
   - Shows aggregate CPU usage percentage
   - Lists individual thread usage percentages
   - Updates every second with real-time data

3. **Memory Monitoring**
   - Displays detailed memory information
   - Shows total physical memory, usage percentages
   - Includes swap memory statistics
   - Positioned on the right side of the terminal

4. **Display Layout**
   - CPU information positioned at top-left (5% from edges)
   - Memory information positioned at top-right (50% across)
   - Automatic boundary checking to prevent display overflow
   - Thread list truncation with "..." indicator when space is limited

### Program Flow:

The application runs in an infinite loop that:
- Waits 1 second between updates
- Checks for user exit input
- Updates CPU and memory statistics
- Clears and redraws the terminal display
- Refreshes the screen

### Expected Display Format:

```
--- CPU Information ---          --- Memory Information ---

Model: Intel(R) Core(TM) i7      Total physical memory: 16384 MB
Cores: 8                         Usage: 45.2%
Threads: 16                      Total swap: 8192 MB
Usage: 23.45%                    Usage: 2.1%

--- Thread Usage ---
Thread  0:  12.34%
Thread  1:  34.56%
Thread  2:   8.90%
...
```

### Dependencies:

- `cpuinfo_manip.h` - CPU information gathering
- `meminfo_manip.h` - Memory information gathering  
- `tui.h` - Terminal user interface functions
