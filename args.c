/**
* Game Of Life
* args.c: Parse program arguments
*
* URL       https://github.com/jyvet/game-of-life-ncurses
* License   MIT
* Author    Jean-Yves VET <contact[at]jean-yves.vet>
* Copyright (c) 2022
******************************************************************************/

#include <argp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "args.h"

/* Expand macro values to string */
#define STR_VALUE(var)   #var
#define STR(var)         STR_VALUE(var)

const char *argp_program_version = "Game Of Life "GOL_VERSION;
const char *argp_program_bug_address = "<"GOL_CONTACT">";

/* Program documentation */
static char doc[] = "John Horton Conway's Game Of Life visualized in a terminal. "
                    "It accepts the following optional arguments:";

/* A description of the mandatory arguments */
static char args_doc[] = "";

/* Options */
static struct argp_option options[] =
{
    {"rows",        'r',  "<value>",    0, "Rows in the grid [default: "
                                            STR(GOL_N_ROW_DEFAULT) "]"},
    {"columns",     'c',  "<value>",    0, "Columns in the grid [default: "
                                            STR(GOL_N_COL_DEFAULT) "]"},
    {"generations", 'g',  "<value>",    0, "Stop the game when this generation "
                                           "is reached [default: "
                                            STR(GOL_N_GEN_DEFAULT) "]"},
    {"delay",       'd',  "<ms>",       0, "Delay in milliseconds before displaying "
                                           "next generation [default: "
                                            STR(GOL_DELAY_MS_DEFAULT) "ms]"},
    {"no-display",  'n',  0,            0, "Disable ncurses display"},
    {"seed",        's',  "<value>",    0, "Change the initial seed"},
    { 0 }
};

/* Parse a single option */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
    gol_args_t *args = state->input;

    switch (key)
    {
        case 'r':
            args->n_row = atol(arg);
            break;
        case 'c':
            args->n_col = atol(arg);
            break;
        case 'g':
            args->n_generation = atol(arg);
            break;
        case 'd':
            args->gen_delay_ms = atol(arg);
            break;
        case 's':
            args->seed = atol(arg);
            break;
        case 'n':
            args->is_display = false;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

/* Argp parser */
static struct argp argp = { options, parse_opt, args_doc, doc };

/**
 * Parse arguments
 *
 * @param   argc[in]        Amount of arguments
 * @param   argv[in]        Array of arguments
 * @param   out_args[out]   Parsed arguments
 */
void
gol_args_retrieve(int argc, char *argv[], gol_args_t *out_args)
{
    /* Set defaults */
    out_args->n_row        = GOL_N_ROW_DEFAULT;
    out_args->n_col        = GOL_N_COL_DEFAULT;
    out_args->n_generation = GOL_N_GEN_DEFAULT;
    out_args->gen_delay_ms = GOL_DELAY_MS_DEFAULT;
    out_args->seed         = time(NULL);
    out_args->is_display   = true;

    argp_parse (&argp, argc, argv, 0, 0, out_args);
}
