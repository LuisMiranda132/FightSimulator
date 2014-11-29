all: robin generator test

robin: ; g++ robin.cpp RedNeural.cpp utilities.cpp -o robin.out -std=c++11

generator:  ; g++ generator.cpp fighter.cpp -o generator.out -std=c++11 

test:  ; g++ test.cpp fighter.cpp RedNeural.cpp utilities.cpp -o test.out -std=c++11 

clean: ; rm *.out

