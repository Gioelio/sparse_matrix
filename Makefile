all: a.out

a.out : main.o
	g++ -o a.out main.o -std=c++11

main.o: main.cpp sparse_matrix.h
	g++ -o main.o -c main.cpp -std=c++11

.PHONY:
clean:
	rm main.o