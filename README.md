Non Gravitar is a 2D retro game heavily inspired on [Gravitar](https://en.wikipedia.org/wiki/Gravitar), made as part of a programming course for [UNIBO](https://www.unibo.it/en).

It shares with the original similar aesthetics and mechanics, with the main exception being the absence of gravity.
If you want more information about this project you can find a brief report (in italian) [here](https://github.com/paolettiandrea/non-gravitar/blob/master/doc/Relazione.pdf).

## Dependencies
    git
    cmake
    make
    
Additional dependencies are handled as git submodules ([`SGE`](https://github.com/paolettiandrea/SGE) and consequently [`SFML`](https://github.com/SFML/SFML) and [`Box2D`](https://github.com/erincatto/box2d)).

## Build
    git clone https://github.com/paolettiandrea/non-gravitar
    cd non-gravitar
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make
    
    ./non-gravitar
    
Using `ccmake .` or `cmake-gui` in the build folder you can find some useful compilation options.
    
Compilation was tested on **Linux** (Manjaro and Fedora) and **Windows** (mingw+gcc).
