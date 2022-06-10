/**
* Game of Life:
* matrix.h: Binary matrix interface
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <unistd.h>

typedef struct _Matrix
{
    size_t  nrow;
    size_t  ncol;
    char   *content;
} Matrix;

static inline char
get_mat(Matrix *m, const size_t row, const size_t col)
{
    return m->content[m->ncol * row + col];
}

static inline void
set_mat(Matrix *m, const size_t row, const size_t col, const char val)
{
    m->content[m->ncol * row + col] = val;
}

void init_rand_mat(Matrix *m, const size_t nrow, const size_t ncol);

Matrix* alloc_mat(const size_t nrow, const size_t ncol);

#endif /* MATRIX_H */
