#!/bin/bash

for j in 0 1 2 3
do
  for i in $(seq 1 5)
  do 
    gcc -O$j -lm relax.c -o rl
    ./rl 1e-5 > sol.dat
    gnuplot map.gp
    tempo=$(grep 'tempo = ' sol.dat | cut -d = -f 2)
    echo $i '  ' $tempo >> temp.dat
  done
done
rm relax.c~
