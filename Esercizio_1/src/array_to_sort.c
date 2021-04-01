#include <stdlib.h>
#include <stdio.h>
#include "array_to_sort.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

unsigned long binary_search(UnsortedArray *array, void *item, unsigned long low, unsigned long high);
void insertion_sort(UnsortedArray *array, unsigned long start, unsigned long last);
void merge_sort(UnsortedArray *array, unsigned long firstPosition, unsigned long lastPosition);
void merge(UnsortedArray *array, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition);

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


// -------------FUNZIONI (MERGE.C)------------------

unsigned long binary_search(UnsortedArray *array, void *item, unsigned long low, unsigned long high){
    /* if (item == NULL) {
    fprintf(stderr, "add_unsorted_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
    } */

    if (high <= low)
        return (array->precedes(array->array[low], item) == -1) ? (low+1) : low;

    unsigned long mid = (low + high) / 2;

    if (array->precedes(array->array[mid], item) == 0)
        return mid + 1;

    if (array->precedes(array->array[low], item) == 1)
        return binary_search(array, item, mid + 1, high);

    return binary_search(array, item, low, mid - 1);
}

void insertion_sort(UnsortedArray *array, unsigned long start, unsigned long last){
    unsigned long i, j, loc;
    void *selected;

    for (i = start + 1; i <= last; i++){
        j = i - 1;
        selected = array->array[i];

        // find location where selected sould be inseretd
        loc = binary_search(array, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc){
            array->array[j + 1] = array->array[j];
            j--;
        }
        array->array[j + 1] = selected;
    }
    return;
}

void merge_sort(UnsortedArray *array, unsigned long firstPosition, unsigned long lastPosition){
    unsigned long middlePosition;
    if (firstPosition < lastPosition){
        // mettere confronto con k
        middlePosition = (firstPosition + lastPosition) / 2;
        merge_sort(array, firstPosition, middlePosition);
        merge_sort(array, middlePosition + 1, lastPosition);
        merge(array, firstPosition, middlePosition, lastPosition);
    }
    return;
}

void merge(UnsortedArray *array, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition){
    // Create L ← A[p..q] and M ← A[q+1..r]
    unsigned long sizeArrayLeft;
    unsigned long sizeArrayRight;

    sizeArrayLeft = middlePosition - firstPosition + 1;
    sizeArrayRight = lastPosition - middlePosition;

    // Declaration arrays
    void *arrayLeftElement[sizeArrayLeft], *arrayRightElement[sizeArrayRight];
    /*
    UnsortedArray *arrayLeft, *arrayRight;

    // Set fields of two arrays
    arrayLeft->array = arrayLeftElement;
    arrayRight->array = arrayRightElement;
    arrayLeft->precedes = array->precedes;
    arrayRight->precedes = array->precedes;
    arrayLeft->array_capacity = 0;
    arrayRight->array_capacity = 0;
    arrayLeft->size = 0;
    arrayRight->size = 0;
*/
    // Create a copy of two sub-arrays
    for (unsigned long i = 0; i < sizeArrayLeft; i++)
        arrayLeftElement[i] = array->array[firstPosition + i];
    for (unsigned long j = 0; j < sizeArrayRight; j++)
        arrayRightElement[j] = array->array[middlePosition + 1 + j];

    // Maintain current index of sub-arrays and main array
    unsigned long indexLeftArray, indexRightArray, indexArray;
    indexLeftArray = 0;
    indexRightArray = 0;
    indexArray = firstPosition;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (indexLeftArray < sizeArrayLeft && indexRightArray < sizeArrayRight){
        if (array->precedes(arrayLeftElement[indexLeftArray], arrayRightElement[indexRightArray]) != 1){
            // per ora sx è minore uguale di destra, non devo effettuare uno cambiamento
            array->array[indexArray] = arrayLeftElement[indexLeftArray];
            indexLeftArray++;
        }
        else{
            array->array[indexArray] = arrayRightElement[indexRightArray];
            indexRightArray++;
        }
        indexArray++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (indexLeftArray < sizeArrayLeft){
        array->array[indexArray] = arrayLeftElement[indexLeftArray];
        indexLeftArray++;
        indexArray++;
    }

    while (indexRightArray < sizeArrayRight){
        array->array[indexArray] = arrayRightElement[indexRightArray];
        indexRightArray++;
        indexArray++;
    }
    return;
}
