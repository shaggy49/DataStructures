#include "edit_distance.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

static void load_array(const char *fileName, ArrayStrings *arrayStrings){
    char buffer[BUFFER_SIZE];
    FILE *fp;
    char *word;

    printf("\nLoading data from file\n");
    fp = fopen(fileName, "r");
    if (fp == NULL){
        fprintf(stderr, "main: unable to open the file");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
        if (edit_distance_add(arrayStrings, buffer) == -1)
            exit(EXIT_FAILURE);
    }

    fclose(fp);
    printf("Data loaded\n");
    return;
}

static void print_array(ArrayStrings *arrayStrings){
	unsigned long size = edit_distance_size(arrayStrings);
	char *arrayword;
	printf("\n----------ARRAY OF WORDS----------\n");
	
    arrayword = edit_distance_get(arrayStrings, 5);
    for (unsigned long i = 0; i < size; ++i){
		arrayword = edit_distance_get(arrayStrings, i);
		dprintf(1,"%s", arrayword);
	}
	printf("\n");
	return;
}

/* It should be invoked with two parameters specifying the two filepath of the two data file */
int main(int argc, char const *argv[]){
    //un array di stringhe che contiene tutte le parole del dizionario
    ArrayStrings *arrayStrings;

	if (argc < 2){
		printf("Usage: unsortedArray_main <fileName>\n");
		exit(EXIT_FAILURE);										
	}

    if ((arrayStrings = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE);
    load_array(argv[1], arrayStrings);
    print_array(arrayStrings);
    edit_distance_free_memory(arrayStrings);
    
    exit(EXIT_SUCCESS);
}
