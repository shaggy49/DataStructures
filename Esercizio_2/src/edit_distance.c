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

int edit_distance_copy_word_from_to(ArrayStrings * firstArray, unsigned long i, ArrayStrings *secondArray, unsigned long j){
    if(firstArray == NULL || secondArray == NULL){
        fprintf(stderr, "edit_distance_copy_word_from_to: parameter cannot be NULL");
        return -1;
    }
    if(i >= firstArray->size || j >= secondArray->size){
        fprintf(stderr, "edit_distance_copy_word_from_to: Index is out of the array bounds");
        return -1;
    }
    strcpy(firstArray->array[i], secondArray->array[j]);
    return 0;
}


/* It actually calculates edit_distance between two words */
int edit_distance(char *word1, char *word2, int *count){
    (*count)++;
    if(strlen(word1) == 0)
        return (int) strlen(word2);
    if(strlen(word2) == 0)
        return (int) strlen(word1);
    else{
        int dNop = (word1[0] == word2[0] ? edit_distance(word1+1, word2+1, count) : INT_MAX);
        int dIns = 1 + edit_distance(word1+1, word2, count);
        int dCanc = 1 + edit_distance(word1, word2+1, count);
        return MIN( MIN(dCanc,dIns), dNop);
    }
}

/* 
* If the macro SHOW_N_REC_CALLS is defined it will be shown more info on recursive memo calls
*/
int edit_distance_classic(char *word1, char *word2){
    int countRecCall = 0, edit=0;
    if((word1 == NULL) || (word2 == NULL)){
        fprintf(stderr, "String parameters cannot be NULL\n");
        return -1;
    }
    edit = edit_distance(word1, word2, &countRecCall);
    #ifdef SHOW_N_REC_CALLS
        printf("Number of recursive calls (classic programming) between %s %s == %d\n", word1, word2, countRecCall);
    #endif
    return edit;
}

/* It stores the results of subproblem inside the matrix pointed by 'arr' parameter */
int memo(char * word1, char * word2, int **arr, int *count){
    (*count)++;
    int lenWord1 = (int) strlen(word1);
    int lenWord2 = (int) strlen(word2);

    if(lenWord1 == 0)
        return lenWord2;
    if(lenWord2 == 0)
        return lenWord1;
    
    if((arr[lenWord1-1][lenWord2-1]) != -1)
        return arr[lenWord1-1][lenWord2-1];
    
    if(word1[0] == word2[0]){
        arr[lenWord1-1][lenWord2-1] = memo(word1 + 1, word2 + 1, arr, count);
        return arr[lenWord1-1][lenWord2-1];
    }
    else{
        int dIns = memo(word1 + 1, word2, arr, count);
        int dCanc = memo(word1, word2 + 1, arr, count);
        arr[lenWord1-1][lenWord2-1] = 1 + MIN(dIns, dCanc); 
        return 1 + MIN(dIns, dCanc);
    }
}

/* 
* If the macro PRINT_DYN_MEMO is defined it will be stamp memo array.
* If the macro SHOW_N_REC_CALLS is defined it will be shown more info on recursive memo calls.
*/
int edit_distance_dyn(char *word1, char *word2) {
    if((word1 == NULL) || (word2 == NULL)){
        fprintf(stderr, "String parameters cannot be NULL\n");
        return -1;
    }
    int result;
    int countRecCall = 0;
    unsigned int lenWord1 = (unsigned) strlen(word1);
    unsigned int lenWord2 = (unsigned) strlen(word2);

    int **arr= (int **) malloc(sizeof(*arr) * (lenWord1));
    for (unsigned int row = 0; row < lenWord1; row++){
        int *values = (int *) malloc(sizeof(int) * (lenWord2));
        arr[row] = values;    
        for (unsigned int column = 0; column < lenWord2; column++){
            arr[row][column] = -1;
        }
    }
    result = memo(word1, word2, arr, &countRecCall);

    #ifdef PRINT_DYN_MEMO
        for(unsigned int i=0; i < lenWord1; i++){
            for(unsigned int j=0; j < lenWord2; j++){
                printf("%d | ", arr[i][j]);
            }
            printf("\n");
        }
    #endif

    #ifdef SHOW_N_REC_CALLS
        printf("Number of recursive calls (dynamic programming) between %s %s == %d\n", word1, word2, countRecCall);
    #endif
    
    for (unsigned int row = 0; row < lenWord1; row++){
        free(arr[row]);
    }
    free(arr);
    return result;
}
