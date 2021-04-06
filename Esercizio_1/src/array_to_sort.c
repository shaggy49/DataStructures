#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_to_sort.h"
#include <unistd.h>

//Initial capacity for the array
#define INITIAL_CAPACITY 2

//Value of K
#define KEY_VALUE 2

long binary_search(UnsortedArray *array, void *item, long low, long high);
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
    UnsortedArray *unsorted_array = (UnsortedArray*)malloc(sizeof(UnsortedArray));
    if (unsorted_array == NULL) {
        fprintf(stderr, "array_to_sort_create: unable to allocate memory for the ordered array");
        exit(EXIT_FAILURE);
    }
    unsorted_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    if (unsorted_array->array == NULL) {
        fprintf(stderr, "array_to_sort_create: unable to allocate memory for the internal array");
        exit(EXIT_FAILURE);
    }
    unsorted_array->size = 0;
    unsorted_array->array_capacity = INITIAL_CAPACITY;
    unsorted_array->precedes = precedes;
    return unsorted_array;
}

void array_to_sort_add(UnsortedArray *unsorted_array, void *element){
    if (unsorted_array == NULL){
        fprintf(stderr, "add_unsorted_array_element: unsorted_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (element == NULL){
        fprintf(stderr, "add_unsorted_array_element: element parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }

    if (unsorted_array->size >= unsorted_array->array_capacity) {
        unsorted_array->array_capacity = 2 * unsorted_array->array_capacity; // Why multiply by 2?
        unsorted_array->array = (void **)realloc(unsorted_array->array, unsorted_array->array_capacity * sizeof(void *));
        if (unsorted_array->array == NULL) {
            fprintf(stderr, "array_to_sort_add: unable to reallocate memory to host the new element");
            exit(EXIT_FAILURE);
        }
    }
    static unsigned long index = 0;
    unsorted_array->array[index] = element;
    index++;
    unsorted_array->size++;
    return;
}

unsigned long array_to_sort_size(UnsortedArray *unsorted_array){
    if (unsorted_array == NULL) {
        fprintf(stderr, "_size: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    return unsorted_array->size;
}

void *array_to_sort_get(UnsortedArray *unsorted_array, unsigned long index){
    if (unsorted_array == NULL) {
        fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (index >= unsorted_array->size) {
        fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", index);
        exit(EXIT_FAILURE);
    }
    return unsorted_array->array[index];
}

void array_to_sort_free_memory(UnsortedArray *unsorted_array){
    if (unsorted_array == NULL){
        fprintf(stderr, "unsorted_array_free_memory: unsorted_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    free(unsorted_array->array);
    free(unsorted_array);
    return;
}

/* function for swap two elements 
void array_to_sort_swap_elem(UnsortedArray *unsorted_array, long firstElem, long secondElem){
    unsigned long size = sizeof(UnsortedArray);
    char buffer[size];
    memcpy(buffer, unsorted_array->array[firstElem], size);
    memcpy(unsorted_array->array[firstElem], unsorted_array->array[secondElem], size);
    memcpy(unsorted_array->array[secondElem], buffer, size);
    return;
}
*/

// -------------FUNZIONI (MERGE.C)------------------
long binary_search(UnsortedArray *unsorted_array, void *item, long low, long high){
    if (high <= low)
        return (unsorted_array->precedes(unsorted_array->array[low], item) == -1) ? (low+1) : low;

    long mid = (low + high) / 2;

    if (unsorted_array->precedes(unsorted_array->array[mid], item) == 0)
        return mid +1;
    else if (unsorted_array->precedes(unsorted_array->array[mid], item) == -1)
        return binary_search(unsorted_array, item, mid + 1, high);
    
    return binary_search(unsorted_array, item, low, mid - 1);
}

void array_to_sort_binary_insertion_sort(UnsortedArray *unsorted_array, unsigned long firstPosition, unsigned long lastPosition){
    long i, j, location;
    void *selected;

    for (i = (signed) firstPosition + 1; i <= (signed) lastPosition; i++){
        j = i-1;
        selected = unsorted_array->array[i];

        // find location where selected sould be inseretd
        location = binary_search(unsorted_array, selected, 0, j);

        // Move all elements after location to create space
        while (j >= location) {
            unsorted_array->array[j + 1] = unsorted_array->array[j];
            j--;
        }
        unsorted_array->array[j + 1] = selected;
    }
    return;
}

void array_to_sort_merge_sort(UnsortedArray *unsorted_array, unsigned long firstPosition, unsigned long lastPosition){
    unsigned long middlePosition;
    unsigned long currentSize = lastPosition - firstPosition + 1;
    if (firstPosition < lastPosition){
        middlePosition = (firstPosition + lastPosition) / 2;
        if (currentSize <= KEY_VALUE){
            array_to_sort_binary_insertion_sort(unsorted_array, firstPosition, middlePosition);
            array_to_sort_binary_insertion_sort(unsorted_array, middlePosition + 1, lastPosition);
        }
        else{
            array_to_sort_merge_sort(unsorted_array, firstPosition, middlePosition);
            array_to_sort_merge_sort(unsorted_array, middlePosition + 1, lastPosition);
        }
        merge(unsorted_array, firstPosition, middlePosition, lastPosition);
    }
    return;
    /*  MERGE_SORT CLASSICO (SENZA k): */
    /* if (firstPosition < lastPosition){
        // mettere confronto con k
        middlePosition = (firstPosition + lastPosition) / 2;
        array_to_sort_merge_sort(unsorted_array, firstPosition, middlePosition);
        array_to_sort_merge_sort(unsorted_array, middlePosition + 1, lastPosition);
        merge(unsorted_array, firstPosition, middlePosition, lastPosition);
    }
    return; */
}

void merge(UnsortedArray *unsorted_array, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition){
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
        arrayLeftElement[i] = unsorted_array->array[firstPosition + i];
    for (unsigned long j = 0; j < sizeArrayRight; j++)
        arrayRightElement[j] = unsorted_array->array[middlePosition + 1 + j];

    // Maintain current index of sub-arrays and main array
    unsigned long indexLeftArray, indexRightArray, indexArray;
    indexLeftArray = 0;
    indexRightArray = 0;
    indexArray = firstPosition;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (indexLeftArray < sizeArrayLeft && indexRightArray < sizeArrayRight){
        if (unsorted_array->precedes(arrayLeftElement[indexLeftArray], arrayRightElement[indexRightArray]) != 1){
            // per ora sx è minore uguale di destra, non devo effettuare uno cambiamento
            unsorted_array->array[indexArray] = arrayLeftElement[indexLeftArray];
            indexLeftArray++;
        }
        else{
            unsorted_array->array[indexArray] = arrayRightElement[indexRightArray];
            indexRightArray++;
        }
        indexArray++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (indexLeftArray < sizeArrayLeft){
        unsorted_array->array[indexArray] = arrayLeftElement[indexLeftArray];
        indexLeftArray++;
        indexArray++;
    }

    while (indexRightArray < sizeArrayRight){
        unsorted_array->array[indexArray] = arrayRightElement[indexRightArray];
        indexRightArray++;
        indexArray++;
    }

    free(arrayLeftElement);
    free(arrayRightElement);
    return;
}