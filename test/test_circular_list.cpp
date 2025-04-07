#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "circular_linked_list.h"

void print_int(int value) {
    printf("%d ", value);
}

START_TEST(test_list_create) {
    CircularList_int* list = circular_list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    CircularList_int* list = circular_list_int_create();
    
    ck_assert(circular_list_int_append(list, 10));
    ck_assert_uint_eq(list->length, 1);
    
    ck_assert(circular_list_int_append(list, 20));
    ck_assert_uint_eq(list->length, 2);
    
    ck_assert(circular_list_int_append(list, 30));
    ck_assert_uint_eq(list->length, 3);
    
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_get_element) {
    CircularList_int* list = circular_list_int_create();
    int value = 0;

    circular_list_int_append(list, 100);
    circular_list_int_append(list, 200);
    circular_list_int_append(list, 300);

    ck_assert(circular_list_int_get(list, 0, &value));
    ck_assert_int_eq(value, 100);

    ck_assert(circular_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 200);

    ck_assert(circular_list_int_get(list, 2, &value));
    ck_assert_int_eq(value, 300);

    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_remove_element) {
    CircularList_int* list = circular_list_int_create();
    int value = 0;

    circular_list_int_append(list, 1);
    circular_list_int_append(list, 2);
    circular_list_int_append(list, 3);
    circular_list_int_append(list, 4);  // Lista: [1, 2, 3, 4]

    ck_assert(circular_list_int_remove_at(list, 1)); // Elimina el 2
    ck_assert_uint_eq(list->length, 3);

    ck_assert(circular_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 3);  // Lista: [1, 3, 4]

    ck_assert(circular_list_int_remove_at(list, 0)); // Elimina el 1
    ck_assert_uint_eq(list->length, 2);

    ck_assert(circular_list_int_get(list, 0, &value));
    ck_assert_int_eq(value, 3);  // Lista: [3, 4]

    circular_list_int_destroy(list);
}
END_TEST

Suite* circular_list_suite(void) {
    Suite* s = suite_create("Circular Linked List");

    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_append_and_length);
    tcase_add_test(tc_core, test_get_element);
    tcase_add_test(tc_core, test_remove_element);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    SRunner* sr = srunner_create(circular_list_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
