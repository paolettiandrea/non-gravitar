Non Gravitar is a 2D retro game heavily inspired on [Gravitar](https://en.wikipedia.org/wiki/Gravitar).

It shares with the original similar aesthetics and mechanics, with the main exception being the absence of gravity.

If you want more information about this project you can find a brief report in italian [here](./doc/Relazione.pdf).

## Dependencies
    git
    cmake
    
Additional dependencies are handled as git submodules ([`SGE`](https://github.com/paolettiandrea/SGE) and consequently `SFML` and `Box2D`).

## Build
    git clone https://github.com/paolettiandrea/non-gravitar
    cd non-gravitar
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make
    
    ./non-gravitar
    
Compilation was tested on **Linux** (Manjaro and Fedora) and **Windows** (minGW+gcc).
