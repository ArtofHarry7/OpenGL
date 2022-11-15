#!/bin/sh
set -e

g++ instructions.cpp -o instructions
g++ maze1.cpp -lglut -lGL -lGLU -o maze1
g++ maze2.cpp -lglut -lGL -lGLU -o maze2
./instructions
./maze1
./maze2
