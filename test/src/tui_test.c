/**
 * @file tui_test.c
 * @author David
 * @brief Here an explanation
 */

#include <assert.h>
#include "../../src/tui.h"

#include <stdio.h>    // For printing test status
#include <unistd.h>   // For sleep() in the drawing test

/**
 * @brief Tests the tui_get_relative_coord function.
 * It initializes ncurses to get terminal dimensions and then checks
 * if relative coordinates are converted correctly.
 */
void test_relative_coord() {
    printf("Testing tui_get_relative_coord...\n");
    ui_init(); // Initialize TUI to get dimensions

    int rows, cols;
    ui_get_dims(&rows, &cols);

    // Test: Top-left corner
    tui_coord_t coord1 = tui_get_relative_coord(0.0f, 0.0f);
    assert(coord1.row == 0);
    assert(coord1.col == 0);
    printf("  [PASS] Top-left (0.0, 0.0)\n");

    // Test: Center
    tui_coord_t coord2 = tui_get_relative_coord(0.5f, 0.5f);
    assert(coord2.row == (int)(rows * 0.5f));
    assert(coord2.col == (int)(cols * 0.5f));
    printf("  [PASS] Center (0.5, 0.5)\n");

    // Test: Bottom-right corner (Note: raw output is rows/cols)
    tui_coord_t coord3 = tui_get_relative_coord(1.0f, 1.0f);
    assert(coord3.row == rows);
    assert(coord3.col == cols);
    printf("  [PASS] Bottom-right (1.0, 1.0)\n");

    // Test: A specific point
    tui_coord_t coord4 = tui_get_relative_coord(0.25f, 0.75f);
    assert(coord4.row == (int)(rows * 0.25f));
    assert(coord4.col == (int)(cols * 0.75f));
    printf("  [PASS] Specific point (0.25, 0.75)\n");

    ui_cleanup(); // Clean up ncurses
    printf("tui_get_relative_coord tests passed.\n\n");
}

/**
 * @brief Tests the tui_clamp_coord function.
 * It initializes ncurses to get dimensions and then checks
 * if coordinates are correctly clamped to terminal bounds.
 */
void test_clamp_coord() {
    printf("Testing tui_clamp_coord...\n");
    ui_init(); // Initialize TUI to get dimensions

    int rows, cols;
    ui_get_dims(&rows, &cols);

    // Test: Coordinate already within bounds
    tui_coord_t coord1 = {rows / 2, cols / 2};
    tui_coord_t clamped1 = tui_clamp_coord(coord1);
    assert(clamped1.row == coord1.row);
    assert(clamped1.col == coord1.col);
    printf("  [PASS] Inside bounds\n");

    // Test: Coordinate below bounds (negative)
    tui_coord_t coord2 = {-5, -10};
    tui_coord_t clamped2 = tui_clamp_coord(coord2);
    assert(clamped2.row == 0);
    assert(clamped2.col == 0);
    printf("  [PASS] Below bounds\n");

    // Test: Coordinate above bounds
    tui_coord_t coord3 = {rows + 5, cols + 10};
    tui_coord_t clamped3 = tui_clamp_coord(coord3);
    assert(clamped3.row == rows - 1);
    assert(clamped3.col == cols - 1);
    printf("  [PASS] Above bounds\n");

    // Test: Mixed bounds (row below, col above)
    tui_coord_t coord4 = {-2, cols + 3};
    tui_coord_t clamped4 = tui_clamp_coord(coord4);
    assert(clamped4.row == 0);
    assert(clamped4.col == cols - 1);
    printf("  [PASS] Mixed bounds 1\n");

    // Test: Mixed bounds (row inside, col below)
    tui_coord_t coord5 = {rows / 4, -1};
    tui_coord_t clamped5 = tui_clamp_coord(coord5);
    assert(clamped5.row == rows / 4);
    assert(clamped5.col == 0);
    printf("  [PASS] Mixed bounds 2\n");

    ui_cleanup(); // Clean up ncurses
    printf("tui_clamp_coord tests passed.\n\n");
}

/**
 * @brief Tests the drawing functions (visual check only).
 * This function draws text at various positions. Since we cannot use
 * assert.h to check terminal output, this requires visual inspection.
 */
void test_drawing() {
    printf("Testing drawing (visual check - will display for 3 seconds)...\n");
    ui_init();
    ui_clear();

    // Draw at a specific (clamped) point
    tui_coord_t pt1 = {1, 1};
    tui_draw_text(pt1, "Top-Left (1, 1)");

    // Draw at the center using relative coordinates
    tui_coord_t pt2 = tui_get_relative_coord(0.5f, 0.45f); // 0.45f to avoid overlapping
    tui_draw_text(pt2, "Center (Relative)");

    // Draw using coordinates that *will* be clamped (negative)
    tui_coord_t pt3 = {-10, -10};
    tui_draw_text(pt3, "<- Clamped Top-Left (-10, -10)");

    // Draw using coordinates that *will* be clamped (over bounds)
    tui_coord_t pt4 = tui_get_relative_coord(1.1f, 1.1f);
    tui_draw_text(pt4, "Clamped Bottom-Right ->");

    ui_refresh();
    sleep(3); // Pause for 3 seconds to allow visual inspection

    ui_cleanup();
    printf("Drawing test finished.\n\n");
}

/**
 * @brief Main function to run all TUI tests.
 */
int main() {
    printf("=========================\n");
    printf("   Running TUI Tests   \n");
    printf("=========================\n\n");

    // Run tests for coordinate functions
    test_relative_coord();
    test_clamp_coord();

    // Run the visual drawing test
    test_drawing();

    printf("=========================\n");
    printf("  All TUI tests done.  \n");
    printf("=========================\n");

    return 0; // Indicate successful execution
}