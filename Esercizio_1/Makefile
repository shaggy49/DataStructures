CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/array_to_sort_main

run: ./bin/array_to_sort_main
	./bin/array_to_sort_main ./unsorted_array_file.csv

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/array_to_sort_main: build/array_to_sort.o build/array_to_sort_main.o $(COMMON_DEPS)
	$(CC) -o bin/array_to_sort_main build/array_to_sort.o build/array_to_sort_main.o

clean:
	$(RM) build/*
	$(RM) bin/*
