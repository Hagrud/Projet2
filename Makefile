CPPFLAGS = -Wall -std=c++11 -g -Wno-write-strings
EXEC = resol
CC = g++
LIBLEX=-lfl
LEX=flex
YACC=bison
NAME=expr


all: dpll/*.cpp main.cpp *.cpp tseitin/$(NAME).tab.cpp tseitin/$(NAME).yy.c tseitin/$(NAME).cpp
	$(CC) -std=c++11 -g -Wall -Wno-write-strings -o resol $^ $(LIBLEX)

color:

tseitin/$(NAME).yy.c :  tseitin/$(NAME).l
	$(LEX)  -o $@ $^

tseitin/$(NAME).tab.cpp : tseitin/$(NAME).ypp
	$(YACC) --report=all -o $@ -d $^

clean:
	rm -f *~ tseitin/$(NAME).yy.c tseitin/$(NAME).tab.cpp tseitin/$(NAME).tab.hpp resol *.o

