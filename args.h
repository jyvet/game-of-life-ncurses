/**
* Game Of Life
* args.h: Parse program arguments
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#ifndef GOL_ARGS_H
#define GOL_ARGS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define GOL_VERSION      "0.1"
#define GOL_CONTACT      "contact[at]jean-yves.vet"

#define GOL_N_ROW_DEFAULT        64  /* Default rows in the mesh */
#define GOL_N_COL_DEFAULT        64  /* Default columns in the mesh */
#define GOL_N_GEN_DEFAULT       100  /* Stop when the generation is reached */
#define GOL_DELAY_MS_DEFAULT    100  /* Delay before deplaying next generation */

typedef struct gol_args
{
    size_t  n_row;
    size_t  n_col;
    size_t  n_generation;
    size_t  gen_delay_ms;
    size_t  seed;
    bool    is_display;
} gol_args_t;

void gol_args_retrieve(int argc, char **argv, gol_args_t *out_args);

#endif /* GOL_ARGS_H */
