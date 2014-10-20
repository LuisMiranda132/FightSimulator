#! /usr/bin/gnuplot

set key outside bottom
set xrange [0:20]
set yrange [0:20]
set term png
set output "500g_5_a.png"
plot "<awk '{if($3 == 1) print}' ./result500g/500g_5.ans.output.s" title "Fuera","<awk '{if($3 == -1) print}' ./result500g/500g_5.ans.output.s" title "Dentro", "./c.dat" with circles title "Circulo"
set term x11
