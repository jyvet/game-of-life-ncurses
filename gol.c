/**
* Game Of Life
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "args.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct _Gol
{
    Matrix *current;
    Matrix *next;
    size_t step;
    size_t changes;
} Gol;

/**
 * Allocate and initialize a Gol structure
 *
 * @param   nrow[in]        Amount of rows
 * @param   ncol[in]        Amout of columns
 * @param   seed[in]        Seed for initializing the matrix
 *
 * @return  Gol             Pointer to the new Gol structure
 */
static Gol*
gol_init(const size_t nrow, const size_t ncol, const size_t seed)
{
    Gol *g = malloc(sizeof(Gol));
    if (g == NULL)
        goto exit;

    g->current = alloc_mat(nrow, ncol);
    g->next = alloc_mat(nrow, ncol);
    g->step = 0;

    /* Initialize randomly */
    srand(seed);
    init_rand_mat(g->current, nrow , ncol);

    return g;

exit:
    printf("Cannot allocate GOL structure\n");
    exit(1);
}

/**
 * Cleanup
 *
 * @param   g[inout]    Pointer to Gol structure to free
 */
static void
gol_fini(Gol *g)
{
    free(g->current->content);
    free(g->current);

    free(g->next->content);
    free(g->next);

    free(g);
}

/**
 * Allocate and initialize a Gol structure
 *
 * @param   m[in]           Input matrix
 * @param   row[in]         Row index
 * @param   col[in]         Column index
 *
 * @return  size_t          Amount of neighbours
 */
static size_t
gol_count_neighbours(Matrix *m, const size_t row, const size_t col)
{
    size_t i, j, count = 0;
    const size_t row_max = m->nrow - 1;
    const size_t col_max = m->ncol - 1;

    for (i = MAX(0, row - 1); i <= MIN(row_max, row + 1); i++)
        for (j = MAX(0, col - 1); j <= MIN(col_max, col + 1); j++)
        {
            if (i == row && j == col)
                continue;
            else
                count += get_mat(m, i, j);
        }

    return count;
}

/**
 * Compute the next generation.
 *
 * @param   g[inout]        Gol structure
 */
static void
gol_compute(Gol *g)
{
    size_t i, j;
    const size_t nrow = g->current->nrow;
    const size_t ncol = g->current->ncol;

    Matrix *current = g->current;
    Matrix *next = g->next;

    g->step++;
    g->changes = 0;

    for (i = 0; i < nrow; i++)
    {
        for (j = 0; j < ncol; j++)
        {
            bool alive = !!get_mat(current, i, j);
            size_t count = gol_count_neighbours(current, i, j);

            if (alive && (count < 2 || count > 3))
            {
                /**
                 * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
                 * 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
                 */
                set_mat(next, i, j, 0); /* Set dead */
                g->changes++;
            }
            else if (alive && (count == 2 || count == 3))
            {
                /**
                 * 2. Any live cell with two or three live neighbours lives on to the next generation.
                 */
                set_mat(next, i, j, 1); /* Set still alive */
            }
            else if (!alive && count == 3)
            {
                /**
                 * 4. Any dead cell with exactly three live neighbours becomes a live cell,
                 * as if by reproduction.
                 */
                set_mat(next, i, j, 1); /* Set alive */
                g->changes++;
            }
            else
                set_mat(next, i, j, 0); /* Reinitialize the cell */
        }
    }

    g->current = next;
    g->next = current;
}

int
main(int argc, char *argv[])
{
    Gol *g;
    gol_args_t args;
    gol_args_retrieve(argc, argv, &args);

    g = gol_init(args.n_row, args.n_col, args.seed);

    size_t t;
    const size_t max_gen = args.n_generation;

    for (t = 0; t < max_gen; t++)
    {
        gol_compute(g);

        if (g->changes == 0)
            break;
    }

    printf("Game of Life [%lux%lu, seed: %lu, max step: %lu] - steps: %lu\n",
           args.n_col, args.n_row, args.seed, args.n_generation, g->step);

    gol_fini(g);

    return 0;
}
