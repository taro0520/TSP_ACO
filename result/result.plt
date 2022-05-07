set grid
set term png
set output 'Output.png'
set xlabel 'x'
set ylabel 'y'
set title 'Ant Colony Optimization Result'
set xrange [0:70]
set xtics 0,10,70
set yrange [0:80]
set ytics 0,10,80
plot 'path_xy.txt' using 2:3 with linespoints  lw 2 pt 7 ps 1.5 title 'path',\