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
 * two pointers to elements and return 0 iff the first element does NOT precede
 * the second one and a number different from zero otherwise.
 * The input parameter cannot be NULL
 */
UnsortedArray *array_to_sort_create(int (*precedes)(void *, void *));

/*
 * It accepts as input a pointer to an ordered array and a pointer to an
 * element. It adds the element to the ordered array in the right position.
 * The input parameters cannot be NULL
 */
void array_to_sort_add(UnsortedArray *, void *); 

/*
 * It accepts as input a pointer to an unsorted array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
unsigned long array_to_sort_size(UnsortedArray*);

/*
 * It accepts as input a pointer to an unsorted array and an integer "i" and
 * it returns the pointer to the i-th element of the ordered array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the ordered array
 */

/* prende l'elemento in posizione 2 campo */
void *array_to_sort_get(UnsortedArray *, unsigned long);

/* It accepts as input a pointer to an unsorted array and
 * it frees the memory allocated to store the ordered array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the ordered array was created. The input parameters cannot be NULL
 */
void array_to_sort_free_memory(UnsortedArray *);


void array_to_sort_swap_elem(UnsortedArray *, unsigned long, unsigned long);

/* It takes an unsorted array as an input and it orders with a hybrid
 * bin-insert-merge-sort algorithm.
 * It takes two other parameters that represents the first and the last
 * position of the array. The input parameters cannot be NULL
 */

//void array_to_sort_bin_ins_merge_sort(UnsortedArray *, unsigned long, unsigned long, int (*compare)(void*, void*));

/* Inoltre, la libreria deve permettere di specificare 
(cioè deve accettare in input) il criterio secondo cui ordinare i dati. 
*/

void array_to_sort_insertion_sort(UnsortedArray *);

#endif // ARRAY_TO_SORT_H
