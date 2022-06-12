/**
* Game Of Life
* matrix.c: Binary matrix
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/**
 * Random initialization of the matrix with binary values.
 *
 * @param   Matrix[out]     Matrix to initialize
 * @param   nrow[in]        Amount of rows
 * @param   ncol[in]        Amout of columns
 */
void
init_rand_mat(Matrix *m, const size_t nrow, const size_t ncol)
{
    size_t i, j;
    for (i = 0; i < nrow; i++)
        for (j = 0; j < ncol; j++)
            set_mat(m, i, j, !(rand() % 2));
}

/**
 * Allocate a matrix.
 *
 * @param   nrow[in]        Amount of rows
 * @param   ncol[in]        Amout of columns
 *
 * @return  Pointer to the new Matrix structure
 */
Matrix*
alloc_mat(const size_t nrow, const size_t ncol)
{
    Matrix *m = malloc(sizeof(Matrix));
    if (m == NULL)
        goto exit;

    m->nrow = nrow;
    m->ncol = ncol;
    m->content = malloc(nrow * ncol * sizeof(char));
    if(m->content == NULL)
        goto exit;

    return m;

exit:
    printf("Cannot allocate matrix\n");
    exit(1);
}
