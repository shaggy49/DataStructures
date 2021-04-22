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

int edit_distance_free_memory(ArrayStrings *);

/* 
 * It calulates the edit distance between two strings.
 */
//int edit_distance_dyn(char *, int, char *, int);

int edit_distance(char *, char *);



#endif //EDIT_DISTANCE
