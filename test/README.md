# Test:

**Test File: `meminfo_test.c`**

  This directory contains the test suite for the `meminfo_manip` module.

  The test file validates the functionality and formatting of the memory info output.

 ### Implemented Tests:

 1. **`assert(info != NULL);`**  
  Ensures the returned pointer is valid.

 1. **`assert(strlen(info) > 0);`**  
  Ensures the returned string is not empty.

 1. **`assert(strstr(info, "MB") != NULL);`**  
  Checks that memory units are present.

 1. **`assert(strstr(info, "Usage") != NULL);`**  
  Confirms that usage percentage information is included.

 ### Expected Output Format:

  The returned string should be similar to:

  Total physical memory: 11861 MB | Usage: 19.48% | Total swap: 4095 MB | Usage: 0.00%

 ### Expected Result:

  When the test runs successfully, it prints:

  All tests passed.

**Test File: `tui_test.c`**

This directory contains the test suite for the `tui` module.

The test file validates the functionality of TUI coordinate handling and drawing operations.

### Implemented Tests:

1. **`test_relative_coord()`**
   - **`assert(coord1.row == 0 && coord1.col == 0);`**  
     Ensures top-left corner (0.0, 0.0) maps correctly.
   
   - **`assert(coord2.row == (int)(rows * 0.5f) && coord2.col == (int)(cols * 0.5f));`**  
     Verifies center coordinates (0.5, 0.5) are calculated properly.
   
   - **`assert(coord3.row == rows && coord3.col == cols);`**  
     Confirms bottom-right corner (1.0, 1.0) mapping.
   
   - **`assert(coord4.row == (int)(rows * 0.25f) && coord4.col == (int)(cols * 0.75f));`**  
     Tests specific relative coordinate conversion (0.25, 0.75).

2. **`test_clamp_coord()`**
   - **`assert(clamped1.row == coord1.row && clamped1.col == coord1.col);`**  
     Ensures coordinates within bounds remain unchanged.
   
   - **`assert(clamped2.row == 0 && clamped2.col == 0);`**  
     Verifies negative coordinates are clamped to (0, 0).
   
   - **`assert(clamped3.row == rows - 1 && clamped3.col == cols - 1);`**  
     Confirms coordinates above bounds are clamped to maximum valid position.
   
   - **`assert(clamped4.row == 0 && clamped4.col == cols - 1);`**  
     Tests mixed boundary conditions (row below, column above bounds).
   
   - **`assert(clamped5.row == rows / 4 && clamped5.col == 0);`**  
     Validates partial clamping (row valid, column below bounds).

3. **`test_drawing()`**
   - Visual verification test that displays text at various positions
   - Tests drawing at specific coordinates, relative coordinates, and clamped coordinates
   - Requires manual inspection during 3-second display period

### Expected Output Format:

The test output should display for three seconds a format interface.

### Expected Result:

When the test runs successfully, it prints detailed pass/fail status for each coordinate test and displays a visual test showing text drawn at various terminal positions for manual verification.