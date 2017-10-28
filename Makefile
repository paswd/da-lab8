COMPILLER=g++
FLAGS=-Wextra -Wall -Werror -pedantic -std=c++11 -O2

all: start

start: main.o
	$(COMPILLER) $(FLAGS) -o da-lab8 main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

clean:
	-rm -f *.o *.gch *.dat da-lab8
