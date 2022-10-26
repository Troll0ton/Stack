all: mstack

mstack: main.o stack.o
	g++ main.o stack.o

main.o: main.cpp
	g++ -c main.cpp

stack.o: stack.cpp
	g++ -c stack.cpp

clean:
	rm -rf *.o
