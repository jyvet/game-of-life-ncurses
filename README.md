[![Makefile CI](https://github.com/jyvet/game-of-life-ncurses/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/jyvet/game-of-life-ncurses/actions/workflows/c-cpp.yml)

Game Of Life
============

This application runs [John Horton Conway's Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
simulation and displays each generation (tick/step) in the terminal.

![Game Of Life ncurses](/data/gol-ncurses.gif)

Dependencies
------------

* **ncurses** *[apt install libncurses5-dev libncursesw5-dev]*


How to build
------------

    % make


How to run
----------

    % ./gol [OPTION...]

Options are:

    -c, --columns=<value>      Columns in the grid [default: 64]
    -d, --delay=<ms>           Delay in milliseconds before displaying next
                               generation [default: 100ms]
    -g, --generations=<value>  Stop the game when this generation is reached
                               [default: 100]
    -n, --no-display           Disable ncurses display
    -r, --rows=<value>         Rows in the grid [default: 64]
    -s, --seed=<value>         Change initial seed
    -?, --help                 Give this help list
        --usage                Give a short usage message
    -V, --version              Print program version

