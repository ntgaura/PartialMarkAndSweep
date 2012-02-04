all: gc

Object.o: Object.cpp Object.h
	g++ -c Object.cpp

main.o: main.cpp
	g++ -c main.cpp

gc: Object.o main.o
	g++ -o gc Object.o main.o

clean:
	rm -f *.o gc

test: check
check: gc
	./gc
