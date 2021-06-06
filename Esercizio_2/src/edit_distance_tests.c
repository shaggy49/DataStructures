#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "edit_distance.h"

/*
 * Test suite for edit_distance.c library
 */

/* -------------------TESTING edit_distance_is_empty()------------------- */

static void test_edit_distance_is_empty_zero_el(){
    ArrayStrings *array_strings = edit_distance_create();
    TEST_ASSERT_TRUE(edit_distance_is_empty(array_strings));
    edit_distance_free_memory(array_strings);
}

static void test_edit_distance_is_empty_one_el(){
    char *string = "ciao";
    ArrayStrings *array_strings = edit_distance_create();
    edit_distance_add(array_strings, string);
    TEST_ASSERT_FALSE(edit_distance_is_empty(array_strings));
    edit_distance_free_memory(array_strings);
}

/* -------------------TESTING edit_distance_size()------------------- */

static void test_edit_distance_size_zero_el(){
    ArrayStrings *array_strings = edit_distance_create();
    TEST_ASSERT_EQUAL(0, edit_distance_size(array_strings));
    edit_distance_free_memory(array_strings);
}

static void test_edit_distance_size_one_el(){
    char *string = "hello";
    ArrayStrings *array_strings = edit_distance_create();
    edit_distance_add(array_strings, string);
    TEST_ASSERT_EQUAL(1, edit_distance_size(array_strings));
    edit_distance_free_memory(array_strings);
}

/* -------------------TESTING edit_distance_add() and edit_distance_get()------------------- */

static void test_edit_distance_add_get_one_el(){
    char *string = "hola";
    ArrayStrings *array_strings = edit_distance_create();
    edit_distance_add(array_strings, string);
    TEST_ASSERT_EQUAL_STRING(string, edit_distance_get(array_strings, 0));
    edit_distance_free_memory(array_strings);
}

/* -------------------TESTING edit_distance_utilities()------------------- */

static void test_edit_distance_classic_two_null() {
    char *str1 = NULL;
    char *str2 = NULL;

    TEST_ASSERT_EQUAL(-1, edit_distance_classic(str1, str2));
}

static void test_edit_distance_dyn_two_null() {
    char *str1 = NULL;
    char *str2 = NULL;

    TEST_ASSERT_EQUAL(-1, edit_distance_dyn(str1, str2));
}

static void test_edit_distance_classic_one_null(){
    char *str1 = NULL;
    char *str2 = "ciao";

    TEST_ASSERT_EQUAL(-1, edit_distance_classic(str1, str2));
}

static void test_edit_distance_dyn_one_null(){
    char *str1 = NULL;
    char *str2 = "ciao";

    TEST_ASSERT_EQUAL(-1, edit_distance_dyn(str1, str2));
}

static void test_edit_distance_classic_one_empty(){
    char *str1 = "";
    char *str2 = "ciao";

    TEST_ASSERT_EQUAL(4, edit_distance_classic(str1, str2));
}

static void test_edit_distance_dyn_one_empty(){
    char *str1 = "";
    char *str2 = "amore";

    TEST_ASSERT_EQUAL(5, edit_distance_dyn(str1, str2));
}

static void test_edit_distance_classic_two_strings(){
    char *str1 = "bao";
    char *str2 = "ciao";

    TEST_ASSERT_EQUAL(3, edit_distance_classic(str1, str2));
}

static void test_edit_distance_dyn_two_strings(){
    char *str1 = "bao";
    char *str2 = "ciao";

    TEST_ASSERT_EQUAL(3, edit_distance_dyn(str1, str2));
}

static void test_edit_distance_classic_two_long_strings(){
    char *str1 = "tastiera";
    char *str2 = "parmigiano";

    TEST_ASSERT_EQUAL(12, edit_distance_classic(str1, str2));
}

static void test_edit_distance_dyn_two_long_strings(){
    char *str1 = "tastiera";
    char *str2 = "parmigiano";

    TEST_ASSERT_EQUAL(12, edit_distance_dyn(str1, str2));
}

int main(){
    UNITY_BEGIN();
/* -------------------TESTING edit_distance_auxiliaries()------------------- */
    RUN_TEST(test_edit_distance_is_empty_zero_el);
    RUN_TEST(test_edit_distance_is_empty_one_el);
    RUN_TEST(test_edit_distance_size_zero_el);
    RUN_TEST(test_edit_distance_size_one_el);
    RUN_TEST(test_edit_distance_add_get_one_el);
/* -------------------TESTING edit_distance_utilities------------------- */
    RUN_TEST(test_edit_distance_classic_two_null);
    RUN_TEST(test_edit_distance_dyn_two_null);
    RUN_TEST(test_edit_distance_classic_one_null);
    RUN_TEST(test_edit_distance_dyn_one_null);
    RUN_TEST(test_edit_distance_classic_one_empty);
    RUN_TEST(test_edit_distance_dyn_one_empty);
    RUN_TEST(test_edit_distance_classic_two_strings);
    RUN_TEST(test_edit_distance_dyn_two_strings);
    RUN_TEST(test_edit_distance_classic_two_long_strings);
    RUN_TEST(test_edit_distance_dyn_two_long_strings);
    return UNITY_END();
}
