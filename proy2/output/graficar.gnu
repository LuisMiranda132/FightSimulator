#! /usr/bin/gnuplot

set key outside bottom
set term png

set output "1000g_7_2.png"
plot "<head -n1000 result1000gn/1000g_7.output" title "Error"

set xrange [0:20]
set yrange [0:20]
set output "1000g_7_a2.png"
plot "<awk '{if($3 == 1) print}' result1000n/1000_7.ans.output" title "Fuera","<awk '{if($3 == -1) print}' result1000n/1000_7.ans.output" title "Dentro", "./c.dat" with circles title "Circulo"

set term x11
#pause -1 "welp"