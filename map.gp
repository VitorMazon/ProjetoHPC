set terminal pdf enhanced font 'Times New Roman'
set output "Relaxacao.pdf"
set view map
set nokey
set size square
plot "sol.dat" matrix w image
set output
