set terminal pdf enhanced font "Times New Roman"
unset key
set view map
set size square
set output "ParaRaio.pdf"
plot 'paraRaio.dat' matrix w image
set output
