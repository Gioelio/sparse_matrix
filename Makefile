all: a.out

a.out : main.o myexception.o test_class.o
	g++ -o a.out test_class.o main.o myexception.o -std=c++0x

main.o: main.cpp sparse_matrix.h
	g++ -o main.o -c main.cpp -std=c++0x

myexception.o: myexception.cpp myexception.h
	g++ -o myexception.o -c myexception.cpp -std=c++0x

test_class.o: test_class.cpp test_class.h
	g++ -o test_class.o -c test_class.cpp -std=c++0x

.PHONY:
clean:
	rm *.o a.out