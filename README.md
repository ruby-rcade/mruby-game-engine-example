# Example mruby game engine

Note: this repository contains a very basic example and is not intended to be a full featured application.

## Installation

Before you can run this example, you need to install a few dependencies:

1. Install [mruby](http://www.mruby.org)
2. Install [SDL](https://www.libsdl.org)
3. Install [Simple2D](https://github.com/simple2d/simple2d)

On Mac OS X, assuming you have already installed [Homebrew](http://brew.sh), you can easily install mruby and SDL:

    brew install mruby sdl2 sdl2_image sdl2_mixer sdl2_ttf

Next, install Simple2D by compiling from source:

    git clone git@github.com:simple2d/simple2d.git
    cd simple2d
    make && make install

If you haven't already cloned this repository, do that now.

    git clone git@github.com:ruby-rcade/mruby-game-engine-example.git
    cd mruby-game-engine-example

## Building the Executable

To run the example, you first need to compile it. In `src/engine.c` you will find the C and mruby code. 
To compile the "engine", run:

    make

This will run the default task defined in the Makefile and compile the code to an executable file called 
`engine`. The "engine program" expects to find a file called `game.rb` in the current directory. 
Starting the program will open a window which will display a square that you can move around using your arrow keys.

    ./engine

