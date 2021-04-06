#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array_to_sort.h"

#define BUFFER_SIZE 1024

typedef struct _record {
	char *string_field;
    int integer_field;
	double floating_field;
} Record;

// -1 precede
// 0 uguali
// 1 maggiore

/*
* It takes as input two pointers to Record.
* It returns -1 if the string field of the first record is smaller than
* the string field of the second one, 0 if the first string record is
* equal to the string field of the second one and 1 if the string field
* of the first record is bigger than the string field of the second one
*/
static int precedes_record_string_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_string_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_string_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1_p = (Record *)r1_p;
	Record *rec2_p = (Record *)r2_p;

	if (strcmp(rec1_p->string_field, rec2_p->string_field) < 0)
		return -1;
	else if (strcmp(rec1_p->string_field, rec2_p->string_field) == 0)
		return 0;
	return 1;
}

/*
* It takes as input two pointers to Record.
* It returns -1 if the integer field of the first record is smaller than
* the integer field of the second one, 0 if the first integer record is
* equal to the integer field of the second one and 1 if the integer field
* of the first record is bigger than the integer field of the second one
*/
static int precedes_record_integer_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_integer_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_integer_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1_p = (Record *)r1_p;
	Record *rec2_p = (Record *)r2_p;
	if (rec1_p->integer_field < rec2_p->integer_field)
		return -1;
	else if (rec1_p->integer_field == rec2_p->integer_field)
		return 0;
	return 1;
}

/*
* It takes as input two pointers to Record.
* It returns -1 if the floating field of the first record is smaller than
* the floating field of the second one, 0 if the first floating record is
* equal to the floating field of the second one and 1 if the floating field
* of the first record is bigger than the floating field of the second one
*/
static int precedes_record_floating_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_floating_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_floating_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1_p = (Record *)r1_p;
	Record *rec2_p = (Record *)r2_p;
	if (rec1_p->floating_field < rec2_p->floating_field)
		return -1;
	else if (rec1_p->floating_field == rec2_p->floating_field)
		return 0;
	return 1;
}

static void free_array(UnsortedArray *unsorted_array){
	unsigned long size = array_to_sort_size(unsorted_array);
	for (unsigned long i = 0; i < size; ++i){
		Record *array_element = (Record *)array_to_sort_get(unsorted_array, i);
		free(array_element->string_field);
		free(array_element);
	}
	array_to_sort_free_memory(unsorted_array);
	return;
}

static void print_array(UnsortedArray *unsorted_array){
	unsigned long size = array_to_sort_size(unsorted_array);
	Record *array_element;
	printf("\n----------ARRAY OF RECORDS----------\n");
	for (unsigned long i = 0; i < size; ++i){
		array_element = (Record *)array_to_sort_get(unsorted_array, i);
		printf("%s, %d, %f\n", array_element->string_field, array_element->integer_field, array_element->floating_field);
	}
	printf("\n");
	return;
}

/* 
	Prende in input il filename del csv da "convertire" in struct OrderedArray
	e inserisce gli elementi ordinandoli.
 */
static void load_array(const char *file_name, UnsortedArray *unsorted_array){
	char buffer[BUFFER_SIZE];
	FILE *fp;

	printf("\nLoading data from file...\n");
	fp = fopen(file_name, "r");
	if (fp == NULL){
		fprintf(stderr, "main: unable to open the file");
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
		Record *record_p = malloc(sizeof(Record));		//problema!!!
		if (record_p == NULL){
			fprintf(stderr, "main: unable to allocate memory for the read record");
			exit(EXIT_FAILURE);
		}
		char *string_field_in_read_line_p = strtok(buffer, ",");
		char *integer_field_in_read_line_p = strtok(NULL, ",");
		char *floating_field_in_read_line_p = strtok(NULL, ",");

		record_p->string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
		if (record_p->string_field == NULL){
			fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
			exit(EXIT_FAILURE);
		}
		strcpy(record_p->string_field, string_field_in_read_line_p);
		record_p->integer_field = atoi(integer_field_in_read_line_p);
		record_p->floating_field = atof(floating_field_in_read_line_p);
		array_to_sort_add(unsorted_array, (void *)record_p);
	}
	fclose(fp);
	printf("\nData loaded\n");
	return;
}

static void test_with_comparison_function(const char *file_name, int (*compare)(void *, void *)){
	UnsortedArray *unsorted_array = array_to_sort_create(compare);
	load_array(file_name, unsorted_array);
	//print_array(unsorted_array);
	unsigned long size = array_to_sort_size(unsorted_array);
	printf("----------Ordino l'array con merge_sort----------\n");
	array_to_sort_merge_sort(unsorted_array, 0, size-1);
	//print_array(unsorted_array);
	free_array(unsorted_array);
	return;
}

//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]){
	if (argc < 2){
		printf("Usage: unsorted_array_main <file_name>\n");
		exit(EXIT_FAILURE);										// da cambiare
	}
	// sono fede, sto impazzendo per cercare di riconnettermi ma tengo duro
	clock_t begin = clock();
    test_with_comparison_function(argv[1], precedes_record_string_field);
    //test_with_comparison_function(argv[1], precedes_record_integer_field);
	//test_with_comparison_function(argv[1], precedes_record_floating_field);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo di esecuzione: %lf \n", time_spent);
	exit(EXIT_SUCCESS);
}
