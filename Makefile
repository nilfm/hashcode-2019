
all: main  
	g++ -o prog main.o

main: main.cc
	g++ -c main.cc -O2

