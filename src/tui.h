/**
 * @file tui.h
 * @author David
 * @brief Here an explanation
 */

#ifndef TUI_H
#define TUI_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* 
 * A structure to hold terminal coordinates.
 * Use 'row' for the vertical coordinate (Y) and 'col' for the horizontal coordinate (X).
 */
typedef struct {
    int row;
    int col;
} tui_coord_t;


typedef struct{
    float x;
    float y;
}display_ax_t;

/* TUI initialization and control functions */
void ui_init(void);
void ui_cleanup(void);
void ui_clear(void);
void ui_refresh(void);
void ui_set_nodelay(bool enabled);
int ui_getch(void);
void ui_get_dims(int *rows, int *cols);

/* Coordinate system helper functions */

/**
 * @brief Computes coordinates based on a relative percentage of the terminal dimensions.
 * 
 * @param row_ratio A value between 0.0 and 1.0 that represents the vertical percentage (e.g., 0.2 for 20% down).
 * @param col_ratio A value between 0.0 and 1.0 that represents the horizontal percentage (e.g., 0.15 for 15% across).
 * @return tui_coord_t The computed coordinate.
 */
tui_coord_t tui_get_relative_coord(float row_ratio, float col_ratio);

/**
 * @brief Clamps the given coordinate within the current terminal bounds.
 * 
 * @param coord The coordinate to clamp.
 * @return tui_coord_t The clamped coordinate.
 */
tui_coord_t tui_clamp_coord(tui_coord_t coord);

/**
 * @brief Draws a text string at the specified coordinate.
 * This function automatically clamps the coordinate so that it stays within visible bounds.
 * 
 * @param pt The coordinate where the text should be drawn.
 * @param text The text string to display.
 */
void tui_draw_text(tui_coord_t pt, const char *text);

#endif // TUI_H