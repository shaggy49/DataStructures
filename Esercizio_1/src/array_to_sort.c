#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_to_sort.h"
#include <unistd.h>

//Initial capacity for the array
#define INITIAL_CAPACITY 1024

//Value of K
#define KEY_VALUE 2

long binary_search(UnsortedArray *array, void *, long, long);
void merge(UnsortedArray *, unsigned long, unsigned long, unsigned long);

//It represents the internal structure of this implementation of ordered arrays
typedef struct _UnsortedArray{
    void **array;
    unsigned long size;
    unsigned long array_capacity;
    int (*precedes)(void *, void *);
} UnsortedArray;


UnsortedArray *array_to_sort_create(int (*precedes)(void *, void *)){
    if (precedes == NULL) {
        fprintf(stderr, "array_to_sort_create: precedes parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    UnsortedArray *unsortedArray = (UnsortedArray*)malloc(sizeof(UnsortedArray));
    if (unsortedArray == NULL) {
        fprintf(stderr, "array_to_sort_create: unable to allocate memory for the ordered array");
        exit(EXIT_FAILURE);
    }
    unsortedArray->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    if (unsortedArray->array == NULL) {
        fprintf(stderr, "array_to_sort_create: unable to allocate memory for the internal array");
        exit(EXIT_FAILURE);
    }
    unsortedArray->size = 0;
    unsortedArray->array_capacity = INITIAL_CAPACITY;
    unsortedArray->precedes = precedes;
    return unsortedArray;
}

void array_to_sort_add(UnsortedArray *unsortedArray, void *element){
    if (unsortedArray == NULL){
        fprintf(stderr, "add_unsortedArray_element: unsortedArray parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (element == NULL){
        fprintf(stderr, "add_unsortedArray_element: element parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }

    if (unsortedArray->size >= unsortedArray->array_capacity) {
        unsortedArray->array_capacity = 2 * unsortedArray->array_capacity; // Why multiply by 2?
        unsortedArray->array = (void **)realloc(unsortedArray->array, unsortedArray->array_capacity * sizeof(void *));
        if (unsortedArray->array == NULL) {
            fprintf(stderr, "array_to_sort_add: unable to reallocate memory to host the new element");
            exit(EXIT_FAILURE);
        }
    }
    static unsigned long index = 0;
    unsortedArray->array[index] = element;
    index++;
    unsortedArray->size++;
    return;
}

unsigned long array_to_sort_size(UnsortedArray *unsortedArray){
    if (unsortedArray == NULL) {
        fprintf(stderr, "_size: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    return unsortedArray->size;
}

void *array_to_sort_get(UnsortedArray *unsortedArray, unsigned long index){
    if (unsortedArray == NULL) {
        fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (index >= unsortedArray->size) {
        fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", index);
        exit(EXIT_FAILURE);
    }
    return unsortedArray->array[index];
}

void array_to_sort_free_memory(UnsortedArray *unsortedArray){
    if (unsortedArray == NULL){
        fprintf(stderr, "unsortedArray_free_memory: unsortedArray parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    free(unsortedArray->array);
    free(unsortedArray);
    return;
}

/* function for swap two elements 
void array_to_sort_swap_elem(UnsortedArray *unsortedArray, long firstElem, long secondElem){
    unsigned long size = sizeof(UnsortedArray);
    char buffer[size];
    memcpy(buffer, unsortedArray->array[firstElem], size);
    memcpy(unsortedArray->array[firstElem], unsortedArray->array[secondElem], size);
    memcpy(unsortedArray->array[secondElem], buffer, size);
    return;
}
*/

// -------------FUNZIONI (MERGE.C)------------------
long binary_search(UnsortedArray *unsortedArray, void *selectedElem, long firstPosition, long lastPosition){
    if (lastPosition < firstPosition)
        return firstPosition;
    else {
        long middlePosition = (firstPosition + lastPosition) / 2;
        if (unsortedArray->precedes(unsortedArray->array[middlePosition], selectedElem) == -1)      //middle precede selected
            return binary_search(unsortedArray, selectedElem, middlePosition + 1, lastPosition);    //richiamo sulla meta di destra
        else                                                                                        //middle è maggiore o uguale di selected
            return binary_search(unsortedArray, selectedElem, firstPosition, middlePosition - 1);   //richiamo sulla meta di sinistra
    }
}

void array_to_sort_binary_insertion_sort(UnsortedArray *unsortedArray, unsigned long firstPosition, unsigned long lastPosition){
    long positionElem, tempPos, finalPositionElem;
    void *selectedElem;                                                 //malloc ????????????

    for (positionElem = (signed) firstPosition + 1; positionElem <= (signed) lastPosition; positionElem++){
        tempPos = positionElem-1;
        selectedElem = unsortedArray->array[positionElem];

        // find position where selected should be inserted
        finalPositionElem = binary_search(unsortedArray, selectedElem, (signed) firstPosition, positionElem-1);

        // Move all elements of one position to the right from tempPosition to the finalPositionElem to create space
        while (tempPos >= finalPositionElem) {
            unsortedArray->array[tempPos + 1] = unsortedArray->array[tempPos];
            tempPos--;
        }
        unsortedArray->array[tempPos+1] = selectedElem;
    }
    return;
}

void array_to_sort_merge_sort(UnsortedArray *unsortedArray, unsigned long firstPosition, unsigned long lastPosition){
    unsigned long middlePosition;
    unsigned long currentSize = lastPosition - firstPosition + 1;
    if (firstPosition < lastPosition){
        middlePosition = (firstPosition + lastPosition) / 2;
        if (currentSize <= KEY_VALUE)
            array_to_sort_binary_insertion_sort(unsortedArray, firstPosition, lastPosition);
        else{
            array_to_sort_merge_sort(unsortedArray, firstPosition, middlePosition);
            array_to_sort_merge_sort(unsortedArray, middlePosition + 1, lastPosition);
            merge(unsortedArray, firstPosition, middlePosition, lastPosition);
        }
    }
    return;
    /*  MERGE_SORT CLASSICO (SENZA k): */
    /* if (firstPosition < lastPosition){
        // mettere confronto con k
        middlePosition = (firstPosition + lastPosition) / 2;
        array_to_sort_merge_sort(unsortedArray, firstPosition, middlePosition);
        array_to_sort_merge_sort(unsortedArray, middlePosition + 1, lastPosition);
        merge(unsortedArray, firstPosition, middlePosition, lastPosition);
    }
    return; */
}

void merge(UnsortedArray *unsortedArray, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition){
    // Create L ← A[p..q] and M ← A[q+1..r]
    unsigned long sizeArrayLeft;
    unsigned long sizeArrayRight;

    sizeArrayLeft = middlePosition - firstPosition + 1;
    sizeArrayRight = lastPosition - middlePosition;

    // Declaration arrays
    void **arrayLeftElement = malloc(sizeof(*arrayLeftElement) * sizeArrayLeft);
    void **arrayRightElement = malloc(sizeof(*arrayRightElement) * sizeArrayRight);

    // Create a copy of two sub-arrays
    for (unsigned long i = 0; i < sizeArrayLeft; i++)
        arrayLeftElement[i] = unsortedArray->array[firstPosition + i];
    for (unsigned long j = 0; j < sizeArrayRight; j++)
        arrayRightElement[j] = unsortedArray->array[middlePosition + 1 + j];

    // Maintain current index of sub-arrays and main array
    unsigned long indexLeftArray, indexRightArray, indexArray;
    indexLeftArray = 0;
    indexRightArray = 0;
    indexArray = firstPosition;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (indexLeftArray < sizeArrayLeft && indexRightArray < sizeArrayRight){
        if (unsortedArray->precedes(arrayLeftElement[indexLeftArray], arrayRightElement[indexRightArray]) != 1){
            // per ora sx è minore uguale di destra, non devo effettuare uno cambiamento
            unsortedArray->array[indexArray] = arrayLeftElement[indexLeftArray];
            indexLeftArray++;
        }
        else{
            unsortedArray->array[indexArray] = arrayRightElement[indexRightArray];
            indexRightArray++;
        }
        indexArray++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (indexLeftArray < sizeArrayLeft){
        unsortedArray->array[indexArray] = arrayLeftElement[indexLeftArray];
        indexLeftArray++;
        indexArray++;
    }

    while (indexRightArray < sizeArrayRight){
        unsortedArray->array[indexArray] = arrayRightElement[indexRightArray];
        indexRightArray++;
        indexArray++;
    }

    free(arrayLeftElement);
    free(arrayRightElement);
    return;
}