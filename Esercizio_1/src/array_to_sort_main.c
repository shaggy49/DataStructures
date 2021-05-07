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

/*
* It takes as input two pointers to Record.
* It returns -1 if the string field of the first record is smaller than
* the string field of the second one, 0 if the first string record is
* equal to the string field of the second one and 1 if the string field
* of the first record is bigger than the string field of the second one
*/
static int compare_record_string_field(void *r1P, void *r2P){
	if (r1P == NULL){
		fprintf(stderr, "compare_record_string_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2P == NULL){
		fprintf(stderr, "compare_record_string_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1P = (Record *)r1P;
	Record *rec2P = (Record *)r2P;

	if (strcmp(rec1P->string_field, rec2P->string_field) < 0)
		return -1;
	else if (strcmp(rec1P->string_field, rec2P->string_field) == 0)
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
static int compare_record_integer_field(void *r1P, void *r2P){
	if (r1P == NULL){
		fprintf(stderr, "compare_record_integer_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2P == NULL){
		fprintf(stderr, "compare_record_integer_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1P = (Record *)r1P;
	Record *rec2P = (Record *)r2P;
	if (rec1P->integer_field < rec2P->integer_field)
		return -1;
	else if (rec1P->integer_field == rec2P->integer_field)
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
static int compare_record_floating_field(void *r1P, void *r2P){
	if (r1P == NULL){
		fprintf(stderr, "compare_record_floating_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2P == NULL){
		fprintf(stderr, "compare_record_floating_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	Record *rec1P = (Record *)r1P;
	Record *rec2P = (Record *)r2P;
	if (rec1P->floating_field < rec2P->floating_field)
		return -1;
	else if (rec1P->floating_field == rec2P->floating_field)
		return 0;
	return 1;
}

static void free_array(UnsortedArray *unsortedArray){
	unsigned long size = array_to_sort_size(unsortedArray);
	for (unsigned long i = 0; i < size; ++i){
		Record *arrayElement = (Record *)array_to_sort_get(unsortedArray, i);
		free(arrayElement->string_field);
		free(arrayElement);
	}
	if (array_to_sort_free_memory(unsortedArray) == -1)
		exit(EXIT_FAILURE);
	return;
}

/*
static void print_array(UnsortedArray *unsortedArray){
	unsigned long size = array_to_sort_size(unsortedArray);
	Record *arrayElement;
	printf("\n----------ARRAY OF RECORDS----------\n");
	for (unsigned long i = 0; i < size; ++i){
		arrayElement = (Record *)array_to_sort_get(unsortedArray, i);
		dprintf(1,"%8d,\t %12s,\t %8d,\t %12f\n", arrayElement->id_field, arrayElement->string_field, arrayElement->integer_field, arrayElement->floating_field);
	}
	printf("\n");
	return;
}
*/

static void write_to_file(UnsortedArray *unsortedArray, unsigned int typeWrite){
	unsigned long size = array_to_sort_size(unsortedArray);
	Record *arrayElement;
	FILE *fp = NULL;
	
	printf("\nCreating file\n");
	if (typeWrite == 1)
		fp = fopen("string_sorted_array.csv", "w");
	else if (typeWrite == 2)
		fp = fopen("integer_sorted_array.csv", "w");	
	else if (typeWrite ==  3)
		fp = fopen("float_sorted_array.csv", "w");	
		
	if (fp == NULL) {
    	printf("file can't be opened\n");
       	exit(EXIT_FAILURE);
   	}

	for (unsigned long i = 0; i < size; ++i){
		arrayElement = (Record *) array_to_sort_get(unsortedArray,i);
		fprintf(fp,"%8d, %12s, %8d, %12f\n", arrayElement->id_field, arrayElement->string_field, arrayElement->integer_field, arrayElement->floating_field);
	}
	fclose(fp);
	printf("Your csv file is now sort, check the new file just made\n");
}

/* 
 * Takes as input the csv filename to convert in UnsortedArray type
 * and insert all the element in the same order as the original file.
 */
static void load_array(const char *fileName, UnsortedArray *unsortedArray){
	char buffer[BUFFER_SIZE];
	FILE *fp;

	printf("\nLoading data from file\n");
	fp = fopen(fileName, "r");
	if (fp == NULL){
		fprintf(stderr, "main: unable to open the file");
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
		Record *recordPointer = malloc(sizeof(Record));
		if (recordPointer == NULL){
			fprintf(stderr, "main: unable to allocate memory for the read record");
			exit(EXIT_FAILURE);
		}
		char *id_field_in_read_line_p = strtok(buffer, ",");
		char *string_field_in_read_line_p = strtok(NULL, ",");
		char *integer_field_in_read_line_p = strtok(NULL, ",");
		char *floating_field_in_read_line_p = strtok(NULL, ",");

		recordPointer->string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
		if (recordPointer->string_field == NULL){
			fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
			exit(EXIT_FAILURE);
		}
		recordPointer->id_field = atoi(id_field_in_read_line_p);
		strcpy(recordPointer->string_field, string_field_in_read_line_p);
		recordPointer->integer_field = atoi(integer_field_in_read_line_p);
		recordPointer->floating_field = atof(floating_field_in_read_line_p);
		if (array_to_sort_add(unsortedArray, (void *)recordPointer) == -1)
			exit(EXIT_FAILURE);
	}
	fclose(fp);
	printf("Data loaded\n");
	return;
}

static void test_with_comparison_function(const char *fileName, int (*compare)(void *, void *), unsigned int typeWrite){
	clock_t begin, end;
	double timeSpent;
	UnsortedArray *unsortedArray;

	if ((unsortedArray = array_to_sort_create(compare)) == NULL)
		exit(EXIT_FAILURE);
	load_array(fileName, unsortedArray);
	unsigned long size = array_to_sort_size(unsortedArray);
	/* printf("\nSorting the file with binary_insertion_sort\n");
	array_to_sort_binary_insertion_sort(unsortedArray, 0, size-1); */
	printf("\nSorting the file with merge_bin_ins_sort\n");
	begin = clock();
	if(array_to_sort_merge_binary_insertion_sort(unsortedArray, 0, size-1) == -1)
		exit(EXIT_FAILURE);
	end = clock();
	printf("End sorting\n");
	timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTime to sort: %lf\n", timeSpent);
	write_to_file(unsortedArray, typeWrite);
	//print_array(unsortedArray);
	free_array(unsortedArray);
	return;
}

/* It should be invoked with one parameter specifying the filepath of the data file */
int main(int argc, char const *argv[]){
	unsigned int numOrd, contErr;

	if (argc < 2){
		printf("Usage: array_to_sort_main <fileName>\n");
		exit(EXIT_FAILURE);										
	}
	
	/* Read a number to decide how to sort the file: 1 string, 2 integer, 3 floating point */
	printf("\nHow do you want to sort the file?\n"); 			
	printf("Type [1] for string, [2] for integer and [3] for floating point:\n");
	for (contErr = 0; contErr < 5; contErr++) {
		if (scanf("%u", &numOrd) != 1){
			printf("scanf failed\n");
			exit(EXIT_FAILURE);	
		}
		if ((1 <= numOrd) && (numOrd<= 3))
			break;
		if (contErr < 4)
			printf("You entered an incorrect number. Try again\n");
		else {
			printf("You entered an incorrect number more than five times\n");
			exit(EXIT_FAILURE);		
		}
	}

	if (numOrd == 1)
		test_with_comparison_function(argv[1], compare_record_string_field, numOrd);
	else if (numOrd == 2)
		test_with_comparison_function(argv[1], compare_record_integer_field, numOrd);
	else if (numOrd == 3)
		test_with_comparison_function(argv[1], compare_record_floating_field, numOrd);

	exit(EXIT_SUCCESS);
}
