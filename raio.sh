#!/bin/bash

gcc -O2 pr.c -lm -o pr
./pr 1e-4 > paraRaio.dat
gnuplot raio.gp

rm pr.c~
