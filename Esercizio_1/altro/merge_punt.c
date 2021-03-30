#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

void merge_sort(int * array, int firstPosition, int lastPosition);
void printArray(int * array, int size);

void merge(int * array, int firstPosition, int middlePosition, int lastPosition) {
    // Create L ← A[p..q] and M ← A[q+1..r]
    int sizeArrayLeft;
    int sizeArrayRight;

    sizeArrayLeft = middlePosition - firstPosition + 1;
    sizeArrayRight = lastPosition - middlePosition;

    int arrayLeft[sizeArrayLeft], arrayRight[sizeArrayRight];

    // Create a copy of two sub-arrays
    for (int i = 0; i < sizeArrayLeft; i++)
        arrayLeft[i] = array[firstPosition + i];
    for (int j = 0; j < sizeArrayRight; j++)
        arrayRight[j] = array[middlePosition + 1 + j];

    // Maintain current index of sub-arrays and main array
    int indexLeftArray, indexRightArray, indexArray;
    indexLeftArray = 0;
    indexRightArray = 0;
    indexArray = firstPosition;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (indexLeftArray < sizeArrayLeft && indexRightArray < sizeArrayRight) {
        if (arrayLeft[indexLeftArray] <= arrayRight[indexRightArray]) {
            // per ora sx è minore uguale di destra, non devo effettuare uno cambiamento
            array[indexArray] = arrayLeft[indexLeftArray];
            indexLeftArray++;
        }
        else {
            array[indexArray] = arrayRight[indexRightArray];
            indexRightArray++;
        }
        indexArray++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (indexLeftArray < sizeArrayLeft) {
        array[indexArray] = arrayLeft[indexLeftArray];
        indexLeftArray++;
        indexArray++;
    }

    while (indexRightArray < sizeArrayRight) {
        array[indexArray] = arrayRight[indexRightArray];
        indexRightArray++;
        indexArray++;
    }
    return;
}

void merge_sort(int * array, int firstPosition, int lastPosition) {
    int middlePosition;
    if (firstPosition < lastPosition) {
        middlePosition = (firstPosition + lastPosition) / 2;
        merge_sort(array, firstPosition, middlePosition);
        merge_sort(array, middlePosition + 1, lastPosition);
        merge(array, firstPosition, middlePosition, lastPosition);
    }
    return;
}

void print_array(int * array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
    return;
}

int main() {
    int * arr;
    int numElem = 8;
    arr = (int *) malloc(numElem*sizeof(*arr));
    bzero(arr, numElem);
    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 2;
    arr[3] = 1;
    arr[4] = 1;
    arr[5] = -5;
    arr[6] = -1;
    arr[7] = -9;

    merge_sort(arr, 0, numElem - 1);
    printf("Sorted array: \n");
    print_array(arr, numElem);

    exit(EXIT_SUCCESS);
}