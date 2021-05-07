CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/array_to_sort_main

tests: bin/array_to_sort_tests
	./bin/array_to_sort_tests

run : ./bin/array_to_sort_main
	./bin/array_to_sort_main ~/Downloads/records.csv

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/array_to_sort_main: build/array_to_sort.o build/array_to_sort_main.o $(COMMON_DEPS)
	$(CC) -o bin/array_to_sort_main build/array_to_sort.o build/array_to_sort_main.o

bin/array_to_sort_tests: build/array_to_sort_tests.o build/array_to_sort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/array_to_sort_tests build/array_to_sort_tests.o build/array_to_sort.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*
	$(RM) ./*.csv
