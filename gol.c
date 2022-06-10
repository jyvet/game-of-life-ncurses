/**
* Game Of Life
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#include "args.h"

int
main(int argc, char *argv[])
{
    gol_args_t args;
    gol_args_retrieve(argc, argv, &args);

    return 0;
}
