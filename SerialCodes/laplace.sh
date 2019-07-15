#!/bin/bash/

gcc -O2 relax.c -lm -o lp
./lp 1e-4 > lp.dat

rm relax.c~
