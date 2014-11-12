echo "" > results.txt

for k in 1 2
do
   for l in 1 2
   do
      for i in 1 2 3 4 5 6 7 8 9 10
      do
	 echo "Running"
	 echo "Fitness: $k, Selector: $l, Corrida $i" >> results.txt
	 python gabil.py iris70.data iris30.data $k $l 0.2 0.8 >> results.txt
	 echo "Done"
      done
   done
done
