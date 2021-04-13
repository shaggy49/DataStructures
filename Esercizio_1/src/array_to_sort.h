#ifndef ARRAY_TO_SORT_H
#define ARRAY_TO_SORT_H

/*
 * An array of any number of elements of any kind
 */
typedef struct _UnsortedArray UnsortedArray;

/* 
 * It creates an empty array and returns the created array.
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and:
 * return -1 if the first element precedes the second one;
 * return 0 if the two elements are equal;
 * return 1 if the first element follows the second one;
 * The input parameter cannot be NULL.
 */
UnsortedArray *array_to_sort_create(int (*preceds)(void *, void *));

/* 
 * It accepts as input a pointer to an unsorted array and
 * it returns 1 iff the unsorted array is empty (0 otherwise).
 * The input parameter cannot be NULL
 */
int array_to_sort_is_empty(UnsortedArray *);

/*
 * It accepts as input a pointer to an unsorted array and a pointer to an
 * element. It adds the element to the unsorted array.
 * The input parameters cannot be NULL.
 */
void array_to_sort_add(UnsortedArray *, void *); 

/*
 * It accepts as input a pointer to an unsorted array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL.
 */
unsigned long array_to_sort_size(UnsortedArray*);

/*
 * It accepts as input a pointer to an unsorted array and an unsigned long "i" and
 * it returns the pointer to the i-th element of the unsorted array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the array.
 */
void *array_to_sort_get(UnsortedArray *, unsigned long);

/* 
 * It accepts as input a pointer to an unsorted array and
 * it frees the memory allocated to store the unsorted array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the ordered array was created. The input parameters cannot be NULL.
 */
void array_to_sort_free_memory(UnsortedArray *);

/* 
 * It takes an unsorted array as an input and it orders with a hybrid
 * bin-insert-merge-sort algorithm.
 * It takes two other parameters that represents the first and the last
 * position of the array. The second and third parameters must be a valid
 * positions within the array otherwise an undefined execution could appear. 
 * The input parameters cannot be NULL.
 */
void array_to_sort_merge_binary_insertion_sort(UnsortedArray *, unsigned long, unsigned long);

#endif // ARRAY_TO_SORT_H
