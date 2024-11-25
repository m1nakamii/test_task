all: main

main: main.o engine.o
	g++ main.o engine.o -o main

main.o: main.cpp engine.h
	g++ -c main.cpp

engine.o: engine.cpp engine.h
	g++ -c engine.cpp

clean:
	rm -f main main.o engine.o