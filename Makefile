all: a.out

a.out : main.o myexception.o
	g++ -o a.out main.o myexception.o -std=c++0x

main.o: main.cpp sparse_matrix.h
	g++ -o main.o -c main.cpp -std=c++0x

myexception.o: myexception.cpp myexception.h
	g++ -o myexception.o -c myexception.cpp -std=c++0x

.PHONY:
clean:
	rm main.o