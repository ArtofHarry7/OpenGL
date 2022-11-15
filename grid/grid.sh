#!/bin/sh
set -e

g++ grid.cpp -lglut -lGL -lGLU -o grid
./grid
