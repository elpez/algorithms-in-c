CC = gcc
SRCS = main.c utilities.c data_structures.c ch03_brute_force.c ch04_decrease_and_conquer.c ch05_divide_and_conquer.c ch06_transform_and_conquer.c


all: $(SRCS) algorithms.h data_structures.h
	$(CC) $(SRCS) -o algorithms -std=c99 -pedantic -Wall -g -lm

clean:
	rm algorithms *.o
