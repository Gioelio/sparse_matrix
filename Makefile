all: a.out

a.out : main.o
	g++ -o a.out main.o -std=c++0x

main.o: main.cpp sparse_matrix.h
	g++ -o main.o -c main.cpp -std=c++0x

.PHONY:
clean:
	rm main.o