#! /bin/bash

echo 'compilando...'
#g++ -std=c++11 -o circulo.out circulo.cpp
make
echo 'done!'

mkdir result1000gn
echo '1000'
for Neuronas in `seq 7 10`
do

    echo 'Corriendo pruebas con ' $Neuronas ':'
    cat datos_testing_n1000.txt datos_testing_n100000.txt | time ./circulo.out 1000 $Neuronas 0.001 > result1000gn/1000g_$Neuronas.output
    mv output.output result1000gn/1000_$Neuronas.ans.output
    echo 'done!'
done
