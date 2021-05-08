#ifndef EDIT_DISTANCE
#define EDIT_DISTANCE

/*
 * An array of strings that contains words of any kind
 */
typedef struct _ArrayStrings ArrayStrings;

/*
 * It creates an ArrayStrings structure to contain words.
 * It returns null on failure. 
 */
ArrayStrings *edit_distance_create();

/*
 * It returns 1 if the strings' array is empty, -1 if the parameter is not valid.
 */
int edit_distance_is_empty(ArrayStrings *);

/*
 * It adds a word to the strings' array parameter.
 * It returns 0 on success, -1 on failure.
 */
int edit_distance_add(ArrayStrings *, char *); 

/*
 * It returns the strings' array size. It returns 0 on failure.
 */
unsigned long edit_distance_size(ArrayStrings*);

/*
 * It extracts a word from strings' arrays.
 * It returns NULL on failure.
 */
char *edit_distance_get(ArrayStrings *, unsigned long);

/*
 * It frees memory.
 * It returns 0 on success, -1 on failure.
 */
int edit_distance_free_memory(ArrayStrings *);

/*
 * It copy word stored in the first parameter array at second parameter index to the 
 * third parameter array at fourth parameter index.
 * It returns 0 on success, -1 on failure.  
 */
int edit_distance_copy_word_from_to(ArrayStrings *, unsigned long, ArrayStrings *, unsigned long);

/* 
 * It calulates the edit distance between two strings.
 * It could be really slow for an enormus amount of words.
 * It returns the Levenshtein's edit_distance on success, -1 on failure.
 */

int edit_distance_classic(char *, char *);

/*
 * It calulates the edit distance between two strings.
 * This version use a recursion dynamic programming solution so the result is calculate fasten.
 * It returns the Levenshtein's edit_distance on success, -1 on failure.
 */
int edit_distance_dyn(char *, char *);

#endif //EDIT_DISTANCE
