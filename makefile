CC = gcc
SRCS = ch03_brute_force.c ch04_decrease_and_conquer.c ch05_divide_and_conquer.c main.c utilities.c data_structures.c


all: $(SRCS) algorithms.h data_structures.h
	$(CC) $(SRCS) -o algorithms -std=c99 -pedantic -Wall -g -lm

clean:
	rm algorithms *.o
