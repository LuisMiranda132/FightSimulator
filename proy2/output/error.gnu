#! /usr/bin/gnuplot

set key outside bottom
set xrange restore
set yrange restore
plot "< head --lines=-2 ./result1000/1000_5.output" title "Error"
pause -1 "Hit any key to continue"
