CPPFLAGS = -Wall -std=c++11
EXEC = resol
CC = g++

all: resol

resol:
	$(CC) $(CPPFLAGS) -o $(EXEC) dpll.cpp parser.cpp checker.cpp

clean:
	rm resol
