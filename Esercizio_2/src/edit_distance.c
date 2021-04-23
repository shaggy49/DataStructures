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
    return arrayStrings;
}

int edit_distance_is_empty(ArrayStrings *arrayStrings) {
    if (arrayStrings == NULL) {
        fprintf(stderr, "unsorted_array_is_empty: unsorted_array parameter cannot be NULL");
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

void edit_distance_set_index_to_add(unsigned long newValue){
    indexNewString = newValue;
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

unsigned long edit_distance(char *word1, char *word2){
    if(strlen(word1) == 0)
        return strlen(word2);
    if(strlen(word2) == 0)
        return strlen(word1);
    else{
        //qui andrebbe inserito qualche controllo per evitare di calcolare più volte la stessa cosa
        unsigned long d_nop = (word1[0] == word2[0] ? edit_distance(word1+1, word2+1) : INT_MAX);
        unsigned long d_canc = 1 + edit_distance(word1, word2+1);
        unsigned long d_ins = 1 + edit_distance(word1+1, word2);
        return MIN( MIN(d_canc,d_ins), d_nop);
    }
}

int distance (const char * word1,
                     unsigned long len1,
                     const char * word2,
                     unsigned long len2)
{
    unsigned long matrix[len1 + 1][len2 + 1];
    unsigned long i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        unsigned long j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                unsigned long delete;
                unsigned long insert;
                unsigned long substitute;
                unsigned long minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}
