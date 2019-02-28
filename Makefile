
all: main input output
	g++ -o prog main.o input.o output.o

main: main.cc
	g++ -c main.cc -O2

input: input.cc
	g++ -c input.cc -O2

output: output.cc
	g++ -c output.cc -O2