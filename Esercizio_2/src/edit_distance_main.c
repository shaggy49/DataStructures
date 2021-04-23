#include "edit_distance.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void remove_char(char* s, char c);

#define BUFFER_SIZE 3200
#define REMOVE_PUNTACTION(word)     remove_char((word), ' '); \
                                    remove_char((word), ','); \
                                    remove_char((word), '.'); \
                                    remove_char((word), ':'); \
                                    remove_char((word), ';'); \
                                    remove_char((word), '\n'); \
                                    remove_char((word), '\t'); \
                                    remove_char((word), '\r');

                                    
static void load_array_dictionary(const char *fileName, ArrayStrings *arrayStrings){
    char buffer[BUFFER_SIZE];
    FILE *fp;

    printf("\nLoading data from file dictionary.txt\n");
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

static void load_array_words(const char *fileName, ArrayStrings *arrayStrings){
    char buffer[BUFFER_SIZE];
    FILE *fp;
    char *word;

    printf("\nLoading data from file correctme.txt\n");
    fp = fopen(fileName, "r");
    if (fp == NULL){
        fprintf(stderr, "main: unable to open the file");
        exit(EXIT_FAILURE);
    }

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
        word = strtok(buffer, " ");
        REMOVE_PUNTACTION(word)
        if (edit_distance_add(arrayStrings, word) == -1)
            exit(EXIT_FAILURE);
        while((word = strtok(NULL, " "))!= NULL){
            REMOVE_PUNTACTION(word)
            if (edit_distance_add(arrayStrings, word) == -1)
                exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
    printf("Data loaded\n");
    return;
}

void remove_char(char* string, char toRemove){
    unsigned int length = (unsigned int) strlen(string);
    unsigned int cont, j = 0;
    for (cont = 0 ; cont < length; cont++){
        if (string[cont] != toRemove)
            string[j++] = string[cont];
    }
    string[j] = '\0';
}

void write_to_file(ArrayStrings *arrayStrings){
	unsigned long size = edit_distance_size(arrayStrings);
	FILE *fp = NULL;
    char *word;
	
	printf("\nCreating file\n");
	fp = fopen("you_are_correct_now.txt", "w");	
	if (fp == NULL) {
    	printf("file can't be opened\n");
       	exit(EXIT_FAILURE);
   	}

	for (unsigned long i = 0; i < size; ++i){
		word = edit_distance_get(arrayStrings,i);
        REMOVE_PUNTACTION(word)
		fprintf(fp,"%s ", word);
	}
    fprintf(fp, "\n");
	fclose(fp);
	printf("Just created correct file\n");
} 

static void print_array(ArrayStrings *arrayStrings){
	unsigned long size = edit_distance_size(arrayStrings);
	char *arrayWord;
	
    for (unsigned long i = 0; i < size; ++i){
		arrayWord = edit_distance_get(arrayStrings, i);
		printf("%s\n", arrayWord);
	}
	printf("\n");
	return;
}

void calculate_edit_distance(ArrayStrings *wordsToCorrect, ArrayStrings *dictonaryWords){
    unsigned long n_wordsToCorrect = edit_distance_size(wordsToCorrect);
    unsigned long n_dictonaryWords = edit_distance_size(dictonaryWords);
    unsigned long i, j_min, min_dist;
    unsigned long edit_calcula;
    
    for(i = 0; i < n_wordsToCorrect; i++){
        edit_calcula = 0;
        min_dist = INT_MAX;
        j_min = INT_MAX;
        for(unsigned long j = 0; j < n_dictonaryWords; j++){
            edit_calcula = edit_distance(edit_distance_get(wordsToCorrect,i), edit_distance_get(dictonaryWords,j));
            /* unsigned long edit_calcula = distance(edit_distance_get(wordsToCorrect,i), n_wordsToCorrect, edit_distance_get(dictonaryWords,j), n_dictonaryWords); */
            if (edit_calcula == 0)
                break;
            else if (edit_calcula < min_dist){
                min_dist = edit_calcula;
                j_min = j;
            }
        }
        if (edit_calcula != 0)
            edit_distance_swap_words(wordsToCorrect, i, dictonaryWords, j_min);
    }    
}

/* It should be invoked with two parameters specifying two data filepaths:
 * the first parameter is the dictonary's filepath to look up for suggestions
 * the second parameter is the txt file's filepath to correct.
 */
int main(int argc, char const *argv[]){
    ArrayStrings *dictonaryWords;
    ArrayStrings *wordsToCorrect;

	if (argc < 3){
		printf("Usage: unsortedArray_main <fileName>\n");
		exit(EXIT_FAILURE);										
	}

    if ((dictonaryWords = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE);
    load_array_dictionary(argv[1], dictonaryWords);
    /* printf("Here is your dictonary file:\n\n"); */
    /* print_array(dictonaryWords); */
    if ((wordsToCorrect = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE);
    
    edit_distance_set_index_to_add(0);
    load_array_words(argv[2], wordsToCorrect);
    printf("\n\nHere is your correctMe file (original):\n\n");
    print_array(wordsToCorrect);

    calculate_edit_distance(wordsToCorrect, dictonaryWords);
    printf("\n\nHere is your correctMe file (just modified):\n\n");
    print_array(wordsToCorrect);
    write_to_file(wordsToCorrect);

    edit_distance_free_memory(dictonaryWords);
    edit_distance_free_memory(wordsToCorrect);
    
    exit(EXIT_SUCCESS);
}
