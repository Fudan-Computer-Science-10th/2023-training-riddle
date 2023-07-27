clean:
	main.o

main.o: main.cpp question.hpp chapter.hpp ui.hpp story.hpp
	g++ -c main.cpp -o main.o

output: main.o
	g++ -O2 main.o -o output

all: main.o output