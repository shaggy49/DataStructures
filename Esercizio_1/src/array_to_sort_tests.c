#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "array_to_sort.h"

extern long binary_search(UnsortedArray *, void *, long, long);
extern void merge(UnsortedArray *, unsigned long, unsigned long, unsigned long);
extern void array_to_sort_merge_sort_modified(UnsortedArray *, unsigned long, unsigned long);
extern void array_to_sort_binary_insertion_sort(UnsortedArray *, unsigned long, unsigned long);

/*
 * Test suite for ordered array data structure and algorithms
 */


/* ---------PRECEDENCE RELATION USED IN TESTS---------- */

static int precedes_string_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_string_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_string_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	char *rec1_p = (char *)r1_p;
	char *rec2_p = (char *)r2_p;

	if (strcmp(rec1_p, rec2_p) < 0)
		return -1;
	else if (strcmp(rec1_p, rec2_p) == 0)
		return 0;
	return 1;
}


static int precedes_integer_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_integer_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_integer_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	int *rec1_p = (int *)r1_p;
	int *rec2_p = (int *)r2_p;
	if (*rec1_p < *rec2_p)
		return -1;
	else if (*rec1_p == *rec2_p)
		return 0;
	return 1;
}


static int precedes_floating_field(void *r1_p, void *r2_p){
	if (r1_p == NULL){
		fprintf(stderr, "precedes_record_floating_field: the first parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (r2_p == NULL){
		fprintf(stderr, "precedes_record_floating_field: the second parameter is a null pointer");
		exit(EXIT_FAILURE);
	}
	double *rec1_p = (double *)r1_p;
	double *rec2_p = (double *)r2_p;
	if (*rec1_p < *rec2_p)
		return -1;
	else if (*rec1_p == *rec2_p)
		return 0;
	return 1;
}

/* -------------------TESTING array_to_sort_is_empty()------------------- */

/*
static void test_array_to_sort_null (){
    UnsortedArray *unsortedArray = array_to_sort_create(NULL);
    TEST_ASSERT_NULL();
}
*/

static void test_array_to_sort_is_empty_zero_el(){
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    TEST_ASSERT_TRUE(array_to_sort_is_empty(unsorted_array_int));
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_is_empty_one_el(){
    int i = -1;
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i);
    TEST_ASSERT_FALSE(array_to_sort_is_empty(unsorted_array_int));
    array_to_sort_free_memory(unsorted_array_int);
}

/* -------------------TESTING array_to_sort_size()------------------- */


static void test_array_to_sort_size_zero_el(){
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    TEST_ASSERT_EQUAL_INT(0, array_to_sort_size(unsorted_array_int));
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_size_one_el(){
    int i1 = -13;
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    TEST_ASSERT_EQUAL_INT(1, array_to_sort_size(unsorted_array_int));
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_size_two_el(){
    int i1 = 143;
    int i2 = -94;
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_add(unsorted_array_int, &i2);
    TEST_ASSERT_EQUAL_INT(2, array_to_sort_size(unsorted_array_int));
    array_to_sort_free_memory(unsorted_array_int);
}

/* -------------------TESTING array_to_sort_add()------------------- */

static void test_array_to_sort_add_get_one_el(){
    int i1 = 330;
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    TEST_ASSERT_EQUAL_PTR(&i1, array_to_sort_get(unsorted_array_int, 0));
    array_to_sort_free_memory(unsorted_array_int);
}

/* -------------------TESTING array_to_sort_binary_search()------------------- */
 
static void test_array_to_sort_binary_search_one_el_string(){
    char *s1 = "genoveffa";
    char *toInsert = "zorro";
    long expectedPosition;
    UnsortedArray *unsorted_array_char = array_to_sort_create(precedes_string_field);
    array_to_sort_add(unsorted_array_char, &s1);
    expectedPosition = binary_search(unsorted_array_char, &toInsert, 0, 0);
    TEST_ASSERT_EQUAL_INT(1, expectedPosition);
    array_to_sort_free_memory(unsorted_array_char);
}


static void test_array_to_sort_binary_search_one_el_int(){
    int i1 = -2;
    int i2= 200;
    int toInsert = -122;
    long expectedPosition;
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_add(unsorted_array_int, &i2);
    expectedPosition = binary_search(unsorted_array_int, &toInsert, 0, 0);
    TEST_ASSERT_EQUAL_INT(0, expectedPosition);
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_binary_search_three_el_float(){
    double d1 = -12.5433;
    double d2 = 32.44;
    double d3 = 1244.000;
    double toInsert = 1.633;
    long expectedPosition;
    UnsortedArray *unsorted_array_float = array_to_sort_create(precedes_floating_field);
    array_to_sort_add(unsorted_array_float, &d1);
    array_to_sort_add(unsorted_array_float, &d2);
    array_to_sort_add(unsorted_array_float, &d3);
    expectedPosition = binary_search(unsorted_array_float, &toInsert, 0, 2);
    TEST_ASSERT_EQUAL_INT(1, expectedPosition);
    array_to_sort_free_memory(unsorted_array_float);
}

/* -------------------TESTING array_to_sort_binary_insertion_sort()------------------- */

static void test_array_to_sort_bin_ins_sort_one_el_int(){
    int i1 = 300;
    int *expectedArray[] = {&i1};
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_binary_insertion_sort(unsorted_array_int, 0, 0);
    int **actualArray = malloc(sizeof(int *));
    actualArray[0] = (int *)array_to_sort_get(unsorted_array_int, 0);
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 1);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_bin_ins_sort_two_el_string(){
    char *s1 = "genoveffa";
    char *s2 = "zorro";
    char **expectedArray[] = {&s1, &s2};
    UnsortedArray *unsorted_array_char = array_to_sort_create(precedes_string_field);
    array_to_sort_add(unsorted_array_char, &s1);
    array_to_sort_add(unsorted_array_char, &s2);
    array_to_sort_binary_insertion_sort(unsorted_array_char, 0, 1);
    char **actualArray = malloc(2 * sizeof(char *));
    for (unsigned long i = 0; i < 2; ++i) {
        actualArray[i] = (char *)array_to_sort_get(unsorted_array_char, i);
    }
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 2);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_char);
}

static void test_array_to_sort_bin_ins_sort_three_el_int(){
    int i1 = 321;
    int i2 = -533209;
    int i3 = -241;
    int *expectedArray[] = {&i2, &i3, &i1};

    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_add(unsorted_array_int, &i2);
    array_to_sort_add(unsorted_array_int, &i3);

    array_to_sort_binary_insertion_sort(unsorted_array_int, 0, 2);

    int **actualArray = malloc(3 * sizeof(int *));
    for (unsigned long i = 0; i < 3; ++i) {
        actualArray[i] = (int *)array_to_sort_get(unsorted_array_int, i);
    }
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 3);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_int);
}

/* -------------------TESTING array_to_sort_merge_binary_insertion_sort()------------------- */

static void test_array_to_sort_merge_bin_one_el_string(){
    char *s1 = "ciao";
    char **expectedArray[] = {&s1};
    UnsortedArray *unsorted_array_char = array_to_sort_create(precedes_string_field);
    array_to_sort_add(unsorted_array_char, &s1);
    array_to_sort_merge_binary_insertion_sort(unsorted_array_char, 0, 0);
    char **actualArray = malloc(sizeof(char *));
    actualArray[0] = (char *)array_to_sort_get(unsorted_array_char, 0);
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 1);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_char);
}

static void test_array_to_sort_merge_bin_three_el_string(){
    char *s1 = "Pasqualino";
    char *s2 = "'giovannuccia";
    char *s3 = "bello uaglione";
    char **expectedArray[] = {&s1, &s2, &s3};

    UnsortedArray *unsorted_array_char = array_to_sort_create(precedes_string_field);
    array_to_sort_add(unsorted_array_char, &s1);
    array_to_sort_add(unsorted_array_char, &s2);
    array_to_sort_add(unsorted_array_char, &s3);

    array_to_sort_merge_binary_insertion_sort(unsorted_array_char, 0, 2);

    char **actualArray = malloc(3 * sizeof(char *));
    for (unsigned long i = 0; i < 3; ++i) {
        actualArray[i] = (char *)array_to_sort_get(unsorted_array_char, i);
    }
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 3);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_char);
}

static void test_array_to_sort_merge_bin_one_el_int(){
    int i1 = 300;
    int *expectedArray[] = {&i1};
    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_merge_binary_insertion_sort(unsorted_array_int, 0, 0);
    int **actualArray = malloc(sizeof(int *));
    actualArray[0] = (int *)array_to_sort_get(unsorted_array_int, 0);
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 1);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_merge_bin_three_el_int(){
    int i1 = 1212;
    int i2 = -5332;
    int i3 = 0;
    int *expectedArray[] = {&i2, &i3, &i1};

    UnsortedArray *unsorted_array_int = array_to_sort_create(precedes_integer_field);
    array_to_sort_add(unsorted_array_int, &i1);
    array_to_sort_add(unsorted_array_int, &i2);
    array_to_sort_add(unsorted_array_int, &i3);

    array_to_sort_merge_binary_insertion_sort(unsorted_array_int, 0, 2);

    int **actualArray = malloc(3 * sizeof(int *));
    for (unsigned long i = 0; i < 3; ++i) {
        actualArray[i] = (int *)array_to_sort_get(unsorted_array_int, i);
    }
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 3);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_int);
}

static void test_array_to_sort_merge_bin_one_el_float(){
    double f1 = 37921.47;
    double *expectedArray[] = {&f1};
    UnsortedArray *unsorted_array_float = array_to_sort_create(precedes_floating_field);
    array_to_sort_add(unsorted_array_float, &f1);
    array_to_sort_merge_binary_insertion_sort(unsorted_array_float, 0, 0);
    double **actualArray = malloc(sizeof(double *));
    actualArray[0] = (double *)array_to_sort_get(unsorted_array_float, 0);
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 1);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_float);
}

static void test_array_to_sort_merge_bin_three_el_float(){
    double f1 = 1212.521;
    double f2 = -5332.520;
    double f3 = 0;
    double *expectedArray[] = {&f2, &f3, &f1};

    UnsortedArray *unsorted_array_float = array_to_sort_create(precedes_floating_field);
    array_to_sort_add(unsorted_array_float, &f1);
    array_to_sort_add(unsorted_array_float, &f2);
    array_to_sort_add(unsorted_array_float, &f3);

    array_to_sort_merge_binary_insertion_sort(unsorted_array_float, 0, 2);

    double **actualArray = malloc(3 * sizeof(double *));
    for (unsigned long i = 0; i < 3; ++i) {
        actualArray[i] = (double *)array_to_sort_get(unsorted_array_float, i);
    }
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, actualArray, 3);
    free(actualArray);
    array_to_sort_free_memory(unsorted_array_float);
}

int main(){
    UNITY_BEGIN();
    
    RUN_TEST(test_array_to_sort_is_empty_zero_el);
    RUN_TEST(test_array_to_sort_is_empty_one_el);
    RUN_TEST(test_array_to_sort_size_zero_el);
    RUN_TEST(test_array_to_sort_size_one_el);
    RUN_TEST(test_array_to_sort_size_two_el);
    RUN_TEST(test_array_to_sort_add_get_one_el);

    RUN_TEST(test_array_to_sort_binary_search_one_el_string);
    RUN_TEST(test_array_to_sort_binary_search_one_el_int);
    RUN_TEST(test_array_to_sort_binary_search_three_el_float);

    RUN_TEST(test_array_to_sort_bin_ins_sort_one_el_int);
    RUN_TEST(test_array_to_sort_bin_ins_sort_two_el_string);
    RUN_TEST(test_array_to_sort_bin_ins_sort_three_el_int);

    RUN_TEST(test_array_to_sort_merge_bin_one_el_string);
    RUN_TEST(test_array_to_sort_merge_bin_three_el_string);
    RUN_TEST(test_array_to_sort_merge_bin_one_el_int);
    RUN_TEST(test_array_to_sort_merge_bin_three_el_int);
    RUN_TEST(test_array_to_sort_merge_bin_one_el_float);
    RUN_TEST(test_array_to_sort_merge_bin_three_el_float);

    return UNITY_END();
}
