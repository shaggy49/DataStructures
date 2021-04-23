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
//int edit_distance_dyn(char *, int, char *, int);

unsigned long edit_distance(char *, char *);

int distance (const char * word1,
                     unsigned long len1,
                     const char * word2,
                     unsigned long len2);



#endif //EDIT_DISTANCE
