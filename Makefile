CPPFLAGS = -Wall -std=c++11 -g
EXEC = resol
CC = g++

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJS = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)
