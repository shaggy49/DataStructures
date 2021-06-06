CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion #-D SHOW_N_REC_CALLS -D PRINT_DYN_MEMO
COMMON_DEPS = src/*.h Makefile

all: bin/edit_distance_main

tests: bin/edit_distance_tests
	./bin/edit_distance_tests

#Insert the path of two file next to ./bin/edit_distance_main
run : ./bin/edit_distance_main 
	./bin/edit_distance_main ~/Downloads/dictionary.txt ~/Downloads/correctme.txt

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
