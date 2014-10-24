#! /bin/bash

echo 'compilando...'
make clean
make
echo 'done!'

mkdir resultIris

DIR=$1
RES="resultIris"

for Neuronas in `seq 2 10`
do
   
   echo 'Corriendo pruebas con ' $Neuronas ':'
   FILE="$RES/resultIrisBinario$Neuronas.txt"
   echo "" > $FILE
   FILE="$RES/resultIrisClase$Neuronas.txt"
   echo "" > $FILE

   for Porc in {50..90..10}
   do
      echo 'Corriendo pruebas entrenando con ' $Porc ' de datos:'

      for Type in {0..1}
      do
	 Typ="Binario"
	 FILE="$RES/resultIrisBinario$Neuronas.txt"
	 if [ $Type -eq 1 ]; then
	    Typ="Clase"
	    FILE="$RES/resultIrisClase$Neuronas.txt"
	 fi
	 ./iris.out "$DIR/iris$Porc.data" "$DIR/irisTest$Porc.data" $((150 *
	 $Porc / 100)) $((150* (100-$Porc)/100)) $Neuronas $Typ $2 >> $FILE
      done
   done
done
