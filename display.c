/**
* Game Of Life
* display.c: Display mesh using ncurses
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#include <ncurses.h>
#include <stdlib.h>
#include <stdarg.h>
#include "display.h"

#define COLOR_TITLE           1
#define COLOR_LIVING_CELL     2
#define COLOR_BOX   COLOR_TITLE

#define CELL_WIDTH            3  /* Amount of char to display a cell in width */
#define TITLE_LINES           1  /* Amount of rows dedicated to the title */
#define TITLE_CHAR_MAX      512  /* Maximum char per line */

/**
 * Display a single cell.
 *
 * @param   row[in]    Row coordinate
 * @param   col[in]    Column coordinate
 * @param   value[in]  Cell value
 */
static void
display_cell(const size_t row, const size_t col, const char value)
{
    if (value == 0)
        return;

    attron(COLOR_PAIR(COLOR_LIVING_CELL));
    mvhline(TITLE_LINES + 1 + row, 1 + CELL_WIDTH * col, ' ', CELL_WIDTH);
    attroff(COLOR_PAIR(COLOR_LIVING_CELL));
}

/**
 * Add a box around the mesh.
 *
 * @param   nrow[in]   Amount of rows
 * @param   ncol[in]   Amout of columns
 */
static void
display_box(const size_t nrow, const size_t ncol)
{
    attron(COLOR_PAIR(COLOR_BOX));
    mvhline(TITLE_LINES, 0, 0 , CELL_WIDTH * ncol + 1);
    mvhline(TITLE_LINES + nrow + 1, 0, 0, CELL_WIDTH * ncol + 1);
    mvvline(TITLE_LINES + 1, 0, 0, nrow);
    mvvline(TITLE_LINES + 1, CELL_WIDTH * ncol + 1, 0, nrow);

    mvaddch(TITLE_LINES, 0, ACS_ULCORNER);
    mvaddch(TITLE_LINES, CELL_WIDTH * ncol + 1, ACS_URCORNER);
    mvaddch(TITLE_LINES + nrow + 1, 0, ACS_LLCORNER);
    mvaddch(TITLE_LINES + nrow + 1, CELL_WIDTH * ncol + 1, ACS_LRCORNER);
    attroff(COLOR_PAIR(COLOR_BOX));
}

/**
 * Uses ncurses to display a binary matrix.
 *
 * @param   m[in]   Input matrix/mesh
 */
void
display_mat(Matrix *m)
{
    size_t i, j;
    const size_t nrow = m->nrow;
    const size_t ncol = m->ncol;

    display_box(nrow, ncol);

    for (i = 0; i < nrow; i++)
        for (j = 0; j < ncol; j++)
            display_cell(i , j, get_mat(m, i, j));

    refresh();
}

/**
 * Initialize ncurses.
 */
void
display_init(void)
{
    /* Start curses mode */
    initscr();

    /* Defining colors */
    start_color();
    init_pair(COLOR_TITLE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_LIVING_CELL, COLOR_BLACK, COLOR_GREEN);

    /* Disabling cursor */
    curs_set(0);
}

/**
 * Finalize ncurses.
 */
void
display_fini(void)
{
    endwin();
}

/**
 * Clear the terminal.
 */
void
display_erase(void)
{
    erase();
}

/**
 * Print title (variadic function like printf).
 *
 * @param   format[in]   Text to display
 */
void
display_title(const char *format, ...)
{
    char title[TITLE_CHAR_MAX];
    va_list args;
    va_start(args, format);

    vsprintf(title, format, args);

    attron(A_BOLD);
    attron(COLOR_PAIR(COLOR_TITLE));
    printw(title);
    attroff(COLOR_PAIR(COLOR_TITLE));
    attroff(A_BOLD);

    va_end(args);
}
