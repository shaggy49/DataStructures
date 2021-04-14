#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array_to_sort.h"

#define BUFFER_SIZE 1024

typedef struct _record {
	int id_field;
	char *string_field;
    int integer_field;
	double floating_field;
} Record;

clock_t begin;
clock_t end;

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

static void free_array(UnsortedArray *unsortedArray){
	unsigned long size = array_to_sort_size(unsortedArray);
	for (unsigned long i = 0; i < size; ++i){
		Record *array_element = (Record *)array_to_sort_get(unsortedArray, i);
		free(array_element->string_field);
		free(array_element);
	}
	array_to_sort_free_memory(unsortedArray);
	return;
}

/*
static void print_array(UnsortedArray *unsortedArray){
	unsigned long size = array_to_sort_size(unsortedArray);
	Record *array_element;
	printf("\n----------ARRAY OF RECORDS----------\n");
	for (unsigned long i = 0; i < size; ++i){
		array_element = (Record *)array_to_sort_get(unsortedArray, i);
		printf("%8d;\t %12s;\t %8d;\t %12f\n", array_element->id_field, array_element->string_field, array_element->integer_field, array_element->floating_field);
	}
	printf("\n");
	return;
}
*/

static void write_to_file(UnsortedArray *unsortedArray, unsigned int type_write){
	unsigned long size = array_to_sort_size(unsortedArray);
	Record *array_element;
	FILE *fp = NULL;
	
	printf("\nCreating file\n");
	if (type_write == 1)
		fp = fopen("string_sorted_array.csv", "w");
	else if (type_write == 2)
		fp = fopen("integer_sorted_array.csv", "w");	
	else if (type_write ==  3)
		fp = fopen("float_sorted_array.csv", "w");	
		
	if (fp == NULL) {
    	printf("file can't be opened\n");
       	exit(EXIT_FAILURE);
   	}

	for (unsigned long i = 0; i < size; ++i){
		array_element = (Record *) array_to_sort_get(unsortedArray,i);
		fprintf(fp,"%8d; %12s; %8d; %12f\n", array_element->id_field, array_element->string_field, array_element->integer_field, array_element->floating_field);
	}
	fclose(fp);
	printf("Your csv file is now sort, check the new file just made\n");
}

/* 
 * Takes as input the csv filename to convert in UnsortedArray type
 * and insert all the element in the same order as the original file.
 */
static void load_array(const char *file_name, UnsortedArray *unsortedArray){
	char buffer[BUFFER_SIZE];
	FILE *fp;

	printf("\nLoading data from file\n");
	fp = fopen(file_name, "r");
	if (fp == NULL){
		fprintf(stderr, "main: unable to open the file");
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
		Record *record_p = malloc(sizeof(Record));
		if (record_p == NULL){
			fprintf(stderr, "main: unable to allocate memory for the read record");
			exit(EXIT_FAILURE);
		}
		char *id_field_in_read_line_p = strtok(buffer, ",");
		char *string_field_in_read_line_p = strtok(NULL, ",");
		char *integer_field_in_read_line_p = strtok(NULL, ",");
		char *floating_field_in_read_line_p = strtok(NULL, ",");

		record_p->string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
		if (record_p->string_field == NULL){
			fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
			exit(EXIT_FAILURE);
		}
		record_p->id_field = atoi(id_field_in_read_line_p);
		strcpy(record_p->string_field, string_field_in_read_line_p);
		record_p->integer_field = atoi(integer_field_in_read_line_p);
		record_p->floating_field = atof(floating_field_in_read_line_p);
		array_to_sort_add(unsortedArray, (void *)record_p);
	}
	fclose(fp);
	printf("Data loaded\n");
	return;
}

static void test_with_comparison_function(const char *file_name, int (*precedes)(void *, void *), unsigned int type_write){
	UnsortedArray *unsortedArray = array_to_sort_create(precedes);
	load_array(file_name, unsortedArray);
	unsigned long size = array_to_sort_size(unsortedArray);
	/* printf("\nSorting the file with binary_insertion_sort\n");
	array_to_sort_binary_insertion_sort(unsortedArray, 0, size-1); */
	printf("\nSorting the file with merge_bin_sort\n");
	begin = clock();
	array_to_sort_merge_binary_insertion_sort(unsortedArray, 0, size-1);
	end = clock();
	printf("End sorting\n");
	write_to_file(unsortedArray, type_write);
	free_array(unsortedArray);	
	return;
}

/* It should be invoked with one parameter specifying the filepath of the data file */
int main(int argc, char const *argv[]){
	unsigned int num_ord, cont_err;

	if (argc < 2){
		printf("----------Usage: unsortedArray_main <file_name>----------\n");
		exit(EXIT_FAILURE);										
	}
	
	/* Read a number to decide how to sort the file: 1 string, 2 integer, 3 floating point */
	printf("\nHow do you want to sort the file?\n"); 			
	printf("Type [1] for string, [2] for integer and [3] for floating point:\n");
	for (cont_err = 0; cont_err < 5; cont_err++) {
		if (scanf("%u", &num_ord) != 1){
			printf("scanf failed\n");
			exit(EXIT_FAILURE);	
		}
		if ((1 <= num_ord) && (num_ord<= 3))
			break;
		if (cont_err < 4)
			printf("You entered an incorrect number. Try again\n");
		else {
			printf("You entered an incorrect number more than five times\n");
			exit(EXIT_FAILURE);		
		}
	}

	if (num_ord == 1)
		test_with_comparison_function(argv[1], precedes_record_string_field, num_ord);
	else if (num_ord == 2)
		test_with_comparison_function(argv[1], precedes_record_integer_field, num_ord);
	else if (num_ord == 3)
		test_with_comparison_function(argv[1], precedes_record_floating_field, num_ord);

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTime to sort: %lf\n", time_spent);
	exit(EXIT_SUCCESS);
}
