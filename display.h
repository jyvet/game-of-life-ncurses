/**
* Game Of Life
* display.h: Display mesh using ncurses
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "matrix.h"

void display_init(void);

void display_fini(void);

void display(const char *title, const size_t ncol, const size_t nrow,
             const size_t seed, const size_t step, Matrix *m);

void display_mat(Matrix *m);

void display_erase(void);

void display_title(const char *format, ...);

#endif /* DISPLAY_H */
