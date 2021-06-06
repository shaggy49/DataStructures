#include "edit_distance.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

void remove_char(char* s, char c);

#define BUFFER_SIZE 1024
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
        REMOVE_PUNTACTION(buffer)
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
    unsigned int j = 0;
    for (unsigned int cont = 0 ; cont < length; cont++){
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

/* 
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
*/

/* 
 * It returns 1 if the word is present in the dictionary, 0 otherwise.
 */
long binary_search_word(ArrayStrings *dictonaryWords, char *word, long firstPosition, long lastPosition){
    if (firstPosition > lastPosition)
        return 0;
    else {
        long middlePosition = (firstPosition + lastPosition) / 2;
        if (strcmp(word, edit_distance_get(dictonaryWords, (unsigned) middlePosition)) == 0){
            return 1;
        }
        else if (strcmp(word, edit_distance_get(dictonaryWords, (unsigned) middlePosition)) < 0)
            return binary_search_word(dictonaryWords, word, firstPosition, middlePosition - 1);
        else
            return binary_search_word(dictonaryWords, word, middlePosition + 1, lastPosition);
    }
}

/*
 * It invokes the edit distance function for the words that there are not in the dictionary and whose difference
 * calcualted between the word to be corrected and the words in the dictionary is lower than the minimum
 * edit_distance until then.
 */
void calculate_edit_distance(ArrayStrings *wordsToCorrect, ArrayStrings *dictonaryWords){
    unsigned long nWordsToCorrect = edit_distance_size(wordsToCorrect);
    unsigned long nDictonaryWords = edit_distance_size(dictonaryWords);
    unsigned long minPosDict;
    int minEdDist, editDistance;

    for(unsigned long i = 0; i < nWordsToCorrect; i++){
        minEdDist = INT_MAX;
        minPosDict = INT_MAX;
        
        if (binary_search_word(dictonaryWords, edit_distance_get(wordsToCorrect,i), 0, (signed) nDictonaryWords - 1) == 0) {
            for(unsigned long j = 0; j < nDictonaryWords; j++){
                int lengthDifference = abs((int) strlen(edit_distance_get(wordsToCorrect,i)) - (int) strlen(edit_distance_get(dictonaryWords,j)));
                if (lengthDifference < minEdDist){
                    editDistance = edit_distance_dyn(edit_distance_get(wordsToCorrect,i), edit_distance_get(dictonaryWords,j));
                    if (editDistance < minEdDist){
                        minEdDist = editDistance;
                        minPosDict = j;
                    }
                }
            }
            printf("minEdDist of: \"%s\" is %d; It will be replaced with ==> \"%s\"\n", edit_distance_get(wordsToCorrect,i), minEdDist, edit_distance_get(dictonaryWords,minPosDict));
            edit_distance_copy_word_from_to(wordsToCorrect, i, dictonaryWords, minPosDict);
        }
    }
}

/* 
 * It should be invoked with two parameters specifying two data filepaths:
 * the first parameter is the dictonary's filepath to look up for suggestions
 * the second parameter is the file's filepath to correct.
 */

int main(int argc, char const *argv[]){
    clock_t begin, end;
	double timeSpent;
    ArrayStrings *dictonaryWords;
    ArrayStrings *wordsToCorrect;
	if (argc < 3){
		printf("Usage: edit_distance_main <dictionaryFileName> <correctMeFileName>\n");
		exit(EXIT_FAILURE);										
	}
    if ((dictonaryWords = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE);
    load_array_dictionary(argv[1], dictonaryWords);

    if ((wordsToCorrect = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE); 
    load_array_words(argv[2], wordsToCorrect);
    
    begin = clock();
    calculate_edit_distance(wordsToCorrect, dictonaryWords);
    end = clock();
    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime to correct: %lf\n", timeSpent);
    
    write_to_file(wordsToCorrect);

    edit_distance_free_memory(dictonaryWords);
    edit_distance_free_memory(wordsToCorrect);
    exit(EXIT_SUCCESS);
}