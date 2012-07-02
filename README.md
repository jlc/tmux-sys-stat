# tmux-sys-stat

Display system statistics in tmux status bar.

## Introduction

tmux-sys-stat is still in early stage of development. It displays system statistics such as memory usage and cpus usage.

It is not configurable (yet) and work only on Mac OS X.
It should be pretty easy to implement and add new system specific classes in order to make it work on other systems (GNU/Linux, FreeBSD...etc.).

This project is largerly inspired from [tmux-mem-cpu-load](https://github.com/thewtex/tmux-mem-cpu-load/) from Matt McCormick.
However, it has been reimplemented in order to work on Mac OS X.

Moreover, [MenuMeters](http://www.ragingmenace.com/software/menumeters/)'s code has been used in order to gather MacOSX system statistics.
Thanks to Alex Harper for his great project!

## Parameters

By default, tmux-sys-stat wait 1 second between reading system statistics. We must set tmux-interval with the same value.

## Compilation / installation

Clone:

    cd ~/src/
    git clone https://github.com/jlc/tmux-sys-stat.git
    cd tmux-sys-stat

Compile:

    make

Symlink somewhere (e.g. $HOME/bin):

    ln -s ~/src/tmux-sys-stat/tmux-sys-stat ~/bin/tmux-sys-stat

Add to PATH:

    export PATH=$PATH:$HOME/bin

## Configure tmux

Add in .tmux.conf:

    set -g status-interval 1
    set -g status-right "#[fg=black,bg=yellow]#(tmux-sys-stat)#[default] - #h %H:%M %d-%b-%y"
    set -g status-right-length 130

## Output example

    80.27% [#### ]73% [#    ]05% [##   ]36% [#    ]04% [###  ]44% [#    ]04% [#    ]20% [#    ]02%  - buddy 16:32 02-Jul-12

