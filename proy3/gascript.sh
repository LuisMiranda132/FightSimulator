echo "" > results2.txt

for k in 0.2 0.5 0.8
do
   for l in 0.2 0.5 0.8
   do
      echo "Running"
      echo "Mutacion: $k, Crossover: $l" >> results2.txt
      python gabil.py iris70.data iris30.data 2 2 $k $l >> results2.txt
      echo "Done"
   done
done
