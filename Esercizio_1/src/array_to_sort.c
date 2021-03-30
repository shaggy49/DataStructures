#include <stdlib.h>
#include <stdio.h>
#include "array_to_sort"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

void merge_sort(UnsortedArray *array, unsigned long firstPosition, unsigned long lastPosition);
void insertion_sort(UnsortedArray * array, unsigned long start, unsigned long last);
unsigned long binary_search(UnsortedArray *array, void *item, unsigned long  low, unsigned long high);
void merge(UnsortedArray *array, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition);

//It represents the internal structure of this implementation of ordered arrays
typedef struct _UnsortedArray {
  void **array;
  unsigned long size;
  unsigned long array_capacity;
  int (*precedes)(void*, void*);
} UnsortedArray;

// -1 precede
// 0 uguali
// 1 maggiore
static int precedes_int_field(void *r1_p, void *r2_p) {
    if (r1_p == NULL) {
        fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (r2_p == NULL) {
        fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    int *r1 = (int)r1_p;
    int *r2 = (int)r2_p;
    if((*r1) < (*r2))
        return -1;
    else((*r1) == (*r2) )
        return 0;
    return 1;
}

// -------------FUNZIONI (MERGE.C)------------------

unsigned long binary_search(UnsortedArray *array, void *item, unsigned long low, unsigned long high){
    /* if (item == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
    } */

    if (high <= low)
        return (array->precedes(array->array[low], item) == -1) ? (low+1) : low);

    unsigned long mid = (low + high) / 2;

    if (array->precedes(array->array[mid], item) == 0)
        return mid + 1;

    if (array->precedes(array->array[low], item) == 1)
        return binarySearch(array, item, mid + 1, high);

    return binarySearch(array, item, low, mid - 1);
}

void insertion_sort(UnsortedArray * array, unsigned long start, unsigned long last){
    unsigned long i, j, loc;
    void *selected;

    for (i = start + 1; i <= last; i++) {
        j = i - 1;
        selected = array->array[i];
        
        // find location where selected sould be inseretd
        loc = binarySearch(array, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc) {
            array->array[j+1] = array->array[j];
            j--;
        }
        array->array[j+1] = selected;
    }
    return;
}

void merge_sort(UnsortedArray *array, unsigned long firstPosition, unsigned long lastPosition){
    unsigned long middlePosition;
    if (firstPosition < lastPosition) {
        // mettere confronto con k
        middlePosition = (firstPosition + lastPosition) / 2;
        merge_sort(array, firstPosition, middlePosition);
        merge_sort(array, middlePosition + 1, lastPosition);
        merge(array, firstPosition, middlePosition, lastPosition);
    }
    return;
}

void merge(UnsortedArray *array, unsigned long firstPosition, unsigned long middlePosition, unsigned long lastPosition) {
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
    while (indexLeftArray < sizeArrayLeft && indexRightArray < sizeArrayRight) {
        if (array->precedes(arrayLeftElement[indexLeftArray], arrayRightElement[indexRightArray]) != 1 ) {
            // per ora sx è minore uguale di destra, non devo effettuare uno cambiamento
            array->array[indexArray] = arrayLeftElement[indexLeftArray];
            indexLeftArray++;
        }
        else {
            array->array[indexArray] = arrayRightElement[indexRightArray];
            indexRightArray++;
        }
        indexArray++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (indexLeftArray < sizeArrayLeft) {
        array->array[indexArray] = arrayLeftElement[indexLeftArray];
        indexLeftArray++;
        indexArray++;
    }

    while (indexRightArray < sizeArrayRight) {
        array->array[indexArray] = arrayRightElement[indexRightArray];
        indexRightArray++;
        indexArray++;
    }
    return;
}


// --------------FUNZIONI DA RIVIDERE (DAL ORDERED_ARRAY)----------
UnsortedArray *array_to_sort_create(int (*precedes)(void *, void *));


void array_to_sort_add(UnsortedArray *, void *); //da rivedere


unsigned long array_to_sort_size(UnsortedArray*);


void *array_to_sort_get(UnsortedArray *, unsigned long);


/* swap ????? */


void array_to_sort_free_memory(UnsortedArray *);


void array_to_sort_bin_ins_merge_sort(UnsortedArray *, unsigned long, unsigned long, int (*compare)(void*, void*));
