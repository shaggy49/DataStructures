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

unsigned int edit_distance(char *word1, char *word2){
    if(strlen(word1) == 0)
        return (unsigned int) strlen(word2);
    if(strlen(word2) == 0)
        return (unsigned int) strlen(word1);
    else{
        //qui andrebbe inserito qualche controllo per evitare di calcolare più volte la stessa cosa
        unsigned int dNop = (word1[0] == word2[0] ? edit_distance(word1+1, word2+1) : INT_MAX);
        unsigned int dIns = 1 + edit_distance(word1+1, word2);
        unsigned int dCanc = 1 + edit_distance(word1, word2+1);
        return MIN( MIN(dCanc,dIns), dNop);
    }
}
/* 
typedef struct _EditDistanceCalculate{
    char ** word1;
    char ** word2;
    unsigned long * edit_distance;
    unsigned long capacity;
} EditDistanceCalculate;

char * edit_dist_calc[3]

unsigned long edit_distance_dyn(char *word1, char *word2){

}


unsigned long edit_distance_dyn(char *word1, char *word2, EditDistanceCalculate memo){
    for (unsigned long cont = 0; cont < memo->capacity; cont++){
        for()
        if ((strcmp(memo->word1[cont], word1) == 1) && (strcmp(memo->word2, word2) == 1))
            return memo->edit_distance;
    }
    else {
        ....qui....e nel main......tico tico tico
        
    }
}
 */
 
//memoization
unsigned int memo(char * word1, char * word2, unsigned int arr[(unsigned int)strlen(word1)][(unsigned int)strlen(word2)]){
    unsigned int lenWord1 = (unsigned int) strlen(word1);
    unsigned int lenWord2 = (unsigned int) strlen(word2);

    if(lenWord1 == 0)
        return lenWord2;
    
    if(lenWord2 == 0)
        return lenWord1;

    if((arr[lenWord1][lenWord2]) > 0)
        return arr[lenWord1][lenWord2];
    
    if(word1[0] == word2[0]){
        arr[lenWord1][lenWord2] = memo(word1 + 1, word2 + 1, arr);
        return memo(word1 + 1, word2 + 1, arr);
    }
    else{
        unsigned int dIns = memo(word1 + 1, word2, arr);
        unsigned int dCanc = memo(word1, word2 + 1, arr);
        
        arr[lenWord1][lenWord2] = 1 + MIN(dIns, dCanc);
        return 1 + MIN(dIns, dCanc);
    }
}
    
unsigned int edit_distance_dyn(char *word1, char *word2) {
    //memoization
    printf("\n%s %s\n", word1, word2);

    unsigned int lenWord1 = (unsigned int) strlen(word1);
    unsigned int lenWord2 = (unsigned int) strlen(word2);

    printf("%u %u\n\n", lenWord1, lenWord2);

    unsigned int arr[lenWord1 + 1][lenWord2 + 1];
    for (unsigned int row = 0; row < lenWord1 + 1; row++){
        for (unsigned int column = 0; column < lenWord2 + 1; column++){
            arr[row][column] = 0;
        }
    }
    return memo(word1, word2, arr);
}
