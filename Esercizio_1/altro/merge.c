#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define KEY_VALUE 2
#define MAX_ELEM 1000000

void merge_sort(int array[], int firstPosition, int lastPosition);
void printArray(int arr[], int size);
void insertionSort(int a[], int start, int last);
int binarySearch(int a[], int item, int low, int high);

void merge(int array[], int firstPosition, int middlePosition, int lastPosition) {
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

void merge_sort(int array[], int firstPosition, int lastPosition) {
    int middlePosition;
    int numElem = lastPosition - firstPosition + 1;
    if (firstPosition < lastPosition) {
        // mettere confronto con k
        middlePosition = (firstPosition + lastPosition) / 2;
        if(numElem <= KEY_VALUE){
            insertionSort(array,firstPosition, middlePosition);
            insertionSort(array,middlePosition+1, lastPosition);
        }else {
            merge_sort(array, firstPosition, middlePosition);
            merge_sort(array, middlePosition + 1, lastPosition);
        }
        merge(array, firstPosition, middlePosition, lastPosition);
    }
    return;
}

void merge_sort_original(int array[], int firstPosition, int lastPosition) {
    
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d\n", arr[i]);
    printf("\n"); 
    return;
}

// A binary search based function
// to find the position
// where item should be inserted 
// in a[low..high]

int binarySearch(int a[], int item, int low, int high) {
    if (high <= low)
        return (item > a[low]) ? (low + 1) : low;
 
    int mid = (low + high) / 2;
 
    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item, mid + 1, high);

    return binarySearch(a, item, low, mid - 1);
}
 
// Function to sort an array a[] of size 'n'

void insertionSort(int a[], int start, int last) {
    int i, loc, j, k, selected;

    for (i = start + 1; i <= last; i++) {
        j = i - 1;
        selected = a[i];

        // find location where selected sould be inseretd

        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space

        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = selected;
    }
}

int main() {
    clock_t begin = clock();
    int a[MAX_ELEM];
    /* Initializes random number generator */
    srand((unsigned) getpid());
    for (int i = 0; i<1000000; i++){
        a[i] = rand() % 500;
    }
    printf("numero di elementi: %ld \n", sizeof(a) / sizeof(a[0]));
    int size =  sizeof(a) / sizeof(a[0]);
    merge_sort(a, 0, size - 1);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo di esecuzione: %lf \n", time_spent);
    printf("Sorted array: \n");
    printArray(a, size);
    printf("Tempo di esecuzione: %lf \n", time_spent);
    //fprintf(stdout, "%lu\n", (unsigned long)time(NULL));
    exit(EXIT_SUCCESS);
}
