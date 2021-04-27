#ifndef EDIT_DISTANCE
#define EDIT_DISTANCE

/*
 * An array of strings that contains words of any kind
 */
typedef struct _ArrayStrings ArrayStrings;

ArrayStrings *edit_distance_create();

int edit_distance_is_empty(ArrayStrings *);

int edit_distance_add(ArrayStrings *, char *); 

unsigned long edit_distance_size(ArrayStrings*);

char *edit_distance_get(ArrayStrings *, unsigned long);

void edit_distance_set_index_to_add(unsigned long);

int edit_distance_free_memory(ArrayStrings *);

int edit_distance_swap_words(ArrayStrings *, unsigned long, ArrayStrings *, unsigned long);

/* 
 * It calulates the edit distance between two strings.
 */

unsigned int edit_distance(char *, char *);

unsigned int edit_distance_dyn(char *, char *);

#endif //EDIT_DISTANCE
