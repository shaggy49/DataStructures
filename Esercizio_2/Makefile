CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/edit_distance_main #bin/edit_distance_tests 

tests: bin/edit_distance_tests
	./bin/edit_distance_tests

run : ./bin/edit_distance_main
	./bin/edit_distance_main ~/Downloads/dictionary_minimal.txt ~/Downloads/correctme.txt 

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_distance_main: build/edit_distance.o build/edit_distance_main.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_main build/edit_distance.o build/edit_distance_main.o

bin/edit_distance_tests: build/edit_distance_tests.o build/edit_distance.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_tests build/edit_distance_tests.o build/edit_distance.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*
	$(RM) ./*.txt
