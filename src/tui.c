/**
 * @file tui.c
 * @author David
 */

#include <ncurses.h> // Added: Ncurses library header
#include <stdbool.h> // Added: Standard boolean types
#include "tui.h"     // Added: Include its own header

/* Initialize ncurses mode and terminal settings */
void ui_init(void) {
    initscr();           // Start ncurses mode
    cbreak();            // Make characters available immediately
    noecho();            // Disable echoing of typed characters
    curs_set(0);         // Hide the cursor
    keypad(stdscr, TRUE);// Enable arrow keys and function keys
}

/* Restore terminal configuration */
void ui_cleanup(void) {
    endwin();
}

/* Clear the screen (buffer) */
void ui_clear(void) {
    erase();
}

/* Update the terminal display with the buffer contents */
void ui_refresh(void) {
    refresh();
}

/* Set non-blocking mode for user input */
void ui_set_nodelay(bool enabled) {
    nodelay(stdscr, enabled ? TRUE : FALSE);
}

/* Retrieve a single character input; returns 1 if 'q' or 'Q' is pressed, 0 otherwise */
int ui_exit(void) {
    int ch = getch(); // Read character (might be ERR if non-blocking and no input)
    return (ch == 'q' || ch == 'Q') ? 1 : 0; // Check for 'q' or 'Q'
}

/* Get the current dimensions of the terminal window */
void ui_get_dims(int *rows, int *cols) {
    getmaxyx(stdscr, *rows, *cols);
}

/* ------------------ Coordinate System Functions ------------------ */

/*
 * Convert relative coordinates (from 0.0 to 1.0)
 * to absolute terminal coordinates based on current dimensions.
 */
tui_coord_t tui_get_relative_coord(float row_ratio, float col_ratio) {
    int rows, cols;
    ui_get_dims(&rows, &cols);
    tui_coord_t coord;
    coord.row = (int)(rows * row_ratio);
    coord.col = (int)(cols * col_ratio);
    return coord;
}

/* Clamp coordinate values so they are within terminal bounds */
tui_coord_t tui_clamp_coord(tui_coord_t coord) {
    int rows, cols;
    ui_get_dims(&rows, &cols);

    if (coord.row < 0)
        coord.row = 0;
    if (coord.col < 0)
        coord.col = 0;
    if (coord.row >= rows)
        coord.row = rows - 1;
    if (coord.col >= cols)
        coord.col = cols - 1;

    return coord;
}

/* Draw text at a specified coordinate after clamping the coordinate to valid values */
void tui_draw_text(tui_coord_t pt, const char *text) {
    tui_coord_t safe_pt = tui_clamp_coord(pt);
    mvprintw(safe_pt.row, safe_pt.col, "%s", text);
}