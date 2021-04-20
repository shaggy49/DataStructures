#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit_distance.h"

#define INITIAL_CAPACITY 1024
#define MIN(x,y) ((x) <= (y) ? (x) : (y))
#define INFINITE 2404040

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
    arrayStrings->array[indexNewString] = word;
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
    
/* ------------------ CALCULATE EDIT_DISTANCE FUNCTIONS ------------------ */

int edit_distance(char *s1, int sizeS1, char *s2, int sizeS2){
    if(sizeS1 == 0)
        return sizeS2;
    if(sizeS2 == 0)
        return sizeS1;
    else{
        int d_nop = (s1[0] == s2[0] ? edit_distance(s1+1, sizeS1-1, s2+1, sizeS2 -1) : INFINITE);
        int d_canc = 1 + edit_distance(s1, sizeS1, s2+1, sizeS2 -1);
        int d_ins = 1 + edit_distance(s1+1, sizeS1-1, s2, sizeS2);
        return MIN( MIN(d_canc,d_ins), d_nop);
    }
}