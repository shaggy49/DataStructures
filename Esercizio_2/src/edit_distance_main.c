#include "edit_distance.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

static void load_array(const char *fileName, ArrayStrings *arrayStrings){
    char buffer[BUFFER_SIZE];
    FILE *fp;

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
	
    for (unsigned long i = 0; i < size; ++i){
		arrayword = edit_distance_get(arrayStrings, i);
		dprintf(1,"%s", arrayword);
	}
	printf("\n");
	return;
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
    load_array(argv[1], dictonaryWords);
    printf("Here is your dictonary file:\n\n");
    print_array(dictonaryWords);
    edit_distance_free_memory(dictonaryWords);

    /*  C'è un problema nell'implementazione della struttura ArrayStrings:
        questa infatti non permette di avere più "istanze" nello stesso eseguibile
        per via della variabile statica che usiamo nell'inserimento e che facciamo ritornare
        a 0 solamente nella free.
        Infatti se provassi a spostare riga 62 dopo la seconda chiamata alla load_array questa mi darebbe
        SEG.
        Bisogna capire se ci servirà questa struttura anche per poter analizzare il correctme perché al limite per quello 
        usiamo solo un array dinamico di char* da capire però come impostare, in ogni caso andrebbe fatta una seconda funzione
        di load_array diversa da quella che usiamo per dictionaryWords.
        La seconda funzione di load per wordsToCorrect serve comunque perché le parole adesso bisogna tokenizzarle diversamente. */
    
    if ((wordsToCorrect = edit_distance_create()) == NULL)
		exit(EXIT_FAILURE);
    load_array(argv[2], wordsToCorrect);
    printf("\n\nHere is your correctMe file:\n\n");
    print_array(wordsToCorrect);
    edit_distance_free_memory(wordsToCorrect);
    
    exit(EXIT_SUCCESS);
}
