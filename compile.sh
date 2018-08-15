#!/usr/bin/env bash
g++  main.cpp RgbImage.cpp   -framework OpenGL -framework GLUT -o main -Wno-deprecated
