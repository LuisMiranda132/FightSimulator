#! /bin/bash

echo 'compilando...'
#g++ -std=c++11 -o circulo.out circulo.cpp
make
echo 'done!'

mkdir result2000g

for Neuronas in `seq 2 10`
do

    echo 'Corriendo pruebas con ' $Neuronas ':'
    cat datos_generados_n2000.txt datos_testing_n1000.txt | time ./circulo.out 2000 $Neuronas 0.01 > result2000g/2000g_$Neuronas.output
    mv output.output result2000g/2000_$Neuronas.ans.output
    echo 'done!'
done
