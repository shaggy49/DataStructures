#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "edit_distance.h"

#define INITIAL_CAPACITY 1024
#define MIN(x,y) ((x) <= (y) ? (x) : (y))

typedef struct _ArrayStrings{
    char **array;
    unsigned long size;
    unsigned long array_capacity;
} ArrayStrings;

/* Index of new string that will be inserted */
static unsigned long indexNewString = 0;

ArrayStrings *edit_distance_create(){
    ArrayStrings *arrayStrings = (ArrayStrings*)malloc(sizeof(ArrayStrings));
    if (arrayStrings == NULL) {
        fprintf(stderr, "edit_distance_create: unable to allocate memory for the array");
        return NULL;
    }
    arrayStrings->array = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
    if (arrayStrings->array == NULL) {
        fprintf(stderr, "edit_distance_create: unable to allocate memory for the internal array");
        return NULL;
    }
    arrayStrings->size = 0;
    arrayStrings->array_capacity = INITIAL_CAPACITY;
    indexNewString = 0;
    return arrayStrings;
}

int edit_distance_is_empty(ArrayStrings *arrayStrings) {
    if (arrayStrings == NULL) {
        fprintf(stderr, "array_strings_is_empty: array_strings parameter cannot be NULL");
        return -1;
    }
    return arrayStrings->size == 0;
}

int edit_distance_add(ArrayStrings *arrayStrings, char *word){
    if (arrayStrings == NULL){
        fprintf(stderr, "edit_distance_add: arrayStrings parameter cannot be NULL");
        return -1;
    }
    if (word == NULL){
        fprintf(stderr, "edit_distance_add: word parameter cannot be NULL");
        return -1;
    }

    if (arrayStrings->size >= arrayStrings->array_capacity) {
        arrayStrings->array_capacity = 2 * arrayStrings->array_capacity;
        arrayStrings->array = (char **)realloc(arrayStrings->array, arrayStrings->array_capacity * sizeof(char *));
        if (arrayStrings->array == NULL) {
            fprintf(stderr, "edit_distance_add: unable to reallocate memory to host the new word");
            return -1;
        }
    }
    arrayStrings->array[indexNewString] = malloc(strlen(word) + 1);
    if (arrayStrings->array[indexNewString] == NULL){
        fprintf(stderr, "edit_distance_add: unable to allocate memory for the word");
        return -1;
    }
    strcpy(arrayStrings->array[indexNewString], word);
    indexNewString++;
    arrayStrings->size++;
    return 0;
}

unsigned long edit_distance_size(ArrayStrings *arrayStrings){
    if (arrayStrings == NULL) {
        fprintf(stderr, "edit_distance_size: arrayStrings parameter cannot be NULL");
        return 0;
    }
    return arrayStrings->size;
}

char *edit_distance_get(ArrayStrings *arrayStrings, unsigned long index){
    if (arrayStrings == NULL) {
        fprintf(stderr, "edit_distance_get: arrayStrings parameter cannot be NULL");
        return NULL;
    }
    if (index >= arrayStrings->size) {
        fprintf(stderr, "edit_distance_get: Index %lu is out of the array bounds", index);
        return NULL;
    }
    return arrayStrings->array[index];
}

int edit_distance_free_memory(ArrayStrings *arrayStrings){
    if(arrayStrings == NULL){
        fprintf(stderr, "edit_distance_free_memory: arrayStrings parameter cannot be NULL");
        return -1;
    }
    indexNewString = 0;
    free(arrayStrings->array);
    free(arrayStrings);
    return 0;
}

/* 
 * swappa dictonaryWords[j] in wordsToCorrect[i] 
 */
int edit_distance_swap_words(ArrayStrings * wordsToCorrect, unsigned long i, ArrayStrings *dictonaryWords, unsigned long j){
    if(wordsToCorrect == NULL || dictonaryWords == NULL){
        fprintf(stderr, "edit_distance_swap_words: parameter cannot be NULL");
        return -1;
    }
    if(i >= wordsToCorrect->size || j >= dictonaryWords->size){
        fprintf(stderr, "edit_distance_swap_words: Index is out of the array bounds");
        return -1;
    }
    strcpy(wordsToCorrect->array[i], dictonaryWords->array[j]);
    return 0;
}


/* ------------------ CALCULATE EDIT_DISTANCE FUNCTIONS ------------------ */
int edit_distance(char *word1, char *word2){
    if(strlen(word1) == 0)
        return (int) strlen(word2);
    if(strlen(word2) == 0)
        return (int) strlen(word1);
    else{
        int dNop = (word1[0] == word2[0] ? edit_distance(word1+1, word2+1) : INT_MAX);
        int dIns = 1 + edit_distance(word1+1, word2);
        int dCanc = 1 + edit_distance(word1, word2+1);
        return MIN( MIN(dCanc,dIns), dNop);
    }
}

int edit_distance_classic(char *word1, char *word2){
    if((word1 == NULL) || (word2 == NULL)){
        fprintf(stderr, "String parameters cannot be NULL\n");
        return -1;
    }
    return edit_distance(word1, word2);
}

int memo(char * word1, char * word2, int **arr){
    int lenWord1 = (int) strlen(word1);
    int lenWord2 = (int) strlen(word2);

    if(lenWord1 == 0)
        return lenWord2;
    
    if(lenWord2 == 0)
        return lenWord1;
 
    if((arr[lenWord1][lenWord2]) > 0)
        return arr[lenWord1][lenWord2];
    
    if(word1[0] == word2[0]){ 
        arr[lenWord1][lenWord2] = memo(word1 + 1, word2 + 1, arr);
        return arr[lenWord1][lenWord2];
    }
    else{
        int dIns = memo(word1 + 1, word2, arr);
        int dCanc = memo(word1, word2 + 1, arr);
        
        arr[lenWord1][lenWord2] = 1 + MIN(dIns, dCanc); //non va bene
        return 1 + MIN(dIns, dCanc);
    }
}
    
int edit_distance_dyn(char *word1, char *word2) {
    if((word1 == NULL) || (word2 == NULL)){
        fprintf(stderr, "String parameters cannot be NULL\n");
        return -1;
    }
    int result;
    unsigned int lenWord1 = (unsigned) strlen(word1);
    unsigned int lenWord2 = (unsigned) strlen(word2);

    int **arr= (int **) malloc(sizeof(*arr) * (lenWord1 + 1));     //array di puntatori a interi
    for (unsigned int row = 0; row < lenWord1 + 1; row++){
        int *values = (int *) malloc(sizeof(int) * (lenWord2 + 1));        //array di puntatori ognuno punta a una zona di memoria 
        arr[row] = values;    
        for (unsigned int column = 0; column < lenWord2 + 1; column++){
            arr[row][column] = 0;
        }
    }
    result = memo(word1, word2, arr);
    for (unsigned int row = 0; row < lenWord1 + 1; row++){
        free(arr[row]);
    }
    free(arr);
    return result;
}
