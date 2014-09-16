# Makefile super op

all: main.o everything exe

main.o: gravity.cpp
	g++ -c gravity.cpp	
	
everything:
	g++ -o gravity gravity.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
		
exe:
	./gravity
	
clear:
	rm *.o
