all: main.cpp parser.cpp
	g++ main.cpp parser.cpp -o main -std=c++11

main.cpp:
	g++ -c main.cpp

parser.cpp:
	g++ -c parser.cpp
