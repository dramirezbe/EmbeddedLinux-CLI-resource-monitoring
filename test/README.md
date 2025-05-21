# Test:

Here explanation


**Test File: `meminfo_test.c`**

  This directory contains the test suite for the `meminfo_manip` module.

  The test file validates the functionality and formatting of the memory info output.

 ### Implemented Tests:

 1. **`assert(info != NULL);`**  
  Ensures the returned pointer is valid.

 2. **`assert(strlen(info) > 0);`**  
  Ensures the returned string is not empty.

 3. **`assert(strstr(info, "MB") != NULL);`**  
  Checks that memory units are present.

 4. **`assert(strstr(info, "Usage") != NULL);`**  
  Confirms that usage percentage information is included.

 ### Expected Output Format:

  The returned string should be similar to:

  Total physical memory: 11861 MB | Usage: 19.48% | Total swap: 4095 MB | Usage: 0.00%

 ### Expected Result:

  When the test runs successfully, it prints:

  All tests passed.


