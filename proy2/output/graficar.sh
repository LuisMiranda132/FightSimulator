#! /bin/bash

i=2

for folder in $(ls)
do
    echo
    echo $folder
    echo
    for file in $(ls $folder/*.output)
    do
        echo $'\t' $i 
        tail -n2 $file
        i=`expr $i + 1`
    done
    i=2
done
