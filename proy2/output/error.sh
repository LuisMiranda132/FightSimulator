#! /bin/bash

for folder in $(ls)
do
    for file in $(ls $folder/*.output)
    do
        echo $file
        result= "filename='./"$file"'" 
        gnuplot -e $result error.gnu
    done
done
