Non Gravitar is a 2D retro game heavily inspired on [Gravitar](https://en.wikipedia.org/wiki/Gravitar).

It shares with the original similar aesthetics and mechanics, with the main exception being the absence of gravity.

## Dependencies
- git
- cmake

## Build
    git clone https://github.com/paolettiandrea/non-gravitar
    cd non-gravitar
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make
    
    ./non-gravitar
    
Build was tested on Linux (Manjaro and Fedora) and Windows (minGW+gcc).