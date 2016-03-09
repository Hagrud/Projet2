CPPFLAGS = -Wall -std=c++11
EXEC = resol
CC = g++

SRC = $(wildcard *.cpp)
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
