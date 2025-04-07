#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#define CIRCULAR_LINKED_LIST_IMPLEMENTATION
#include "circular_linked_list.h"

// Función auxiliar para imprimir enteros (usada en pruebas)
void print_int(int value) {
    printf("%d ", value);
}

// Función auxiliar para comparar enteros
bool int_cmp(int a, int b) {
    return a == b;
}

/* ------------------------------------- */
/* Tests para listas circulares de enteros (CircularList_int) */
/* ------------------------------------- */

START_TEST(test_create_circular_list) {
    CircularList_int* list = circular_list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->tail);  // La lista comienza vacía
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

START_TEST(test_get) {
    CircularList_int* list = circular_list_int_create();
    int value = 0;
    
    circular_list_int_append(list, 10);
    circular_list_int_append(list, 20);
    circular_list_int_append(list, 30);
    
    ck_assert(circular_list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    
    ck_assert(circular_list_int_get(list, 2, &value));
    ck_assert_int_eq(value, 30);
    
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_remove_at) {
    CircularList_int* list = circular_list_int_create();
    circular_list_int_append(list, 10);
    circular_list_int_append(list, 20);
    circular_list_int_append(list, 30);
    circular_list_int_append(list, 40);
    
    ck_assert(circular_list_int_remove_at(list, 1));  // Elimina 20
    ck_assert_uint_eq(list->length, 3);
    
    int value = 0;
    ck_assert(circular_list_int_get(list, 1, &value));  // Debería ser 30
    ck_assert_int_eq(value, 30);
    
    ck_assert(circular_list_int_remove_at(list, 0));  // Elimina 10
    ck_assert_uint_eq(list->length, 2);
    
    ck_assert(circular_list_int_get(list, 0, &value));  // Debería ser 30
    ck_assert_int_eq(value, 30);
    
    circular_list_int_destroy(list);
}
END_TEST

START_TEST(test_print) {
    CircularList_int* list = circular_list_int_create();
    circular_list_int_append(list, 10);
    circular_list_int_append(list, 20);
    circular_list_int_append(list, 30);
    
    printf("Lista circular: ");
    circular_list_int_print(list, print_int);  // Debería imprimir: 10 20 30
    
    circular_list_int_destroy(list);
}
END_TEST

/* ------------------------------------- */
/* Suite de pruebas principal */
/* ------------------------------------- */

Suite* circular_linked_list_suite(void) {
    Suite* s = suite_create("Circular Linked List");
    
    TCase* tc_core = tcase_create("Core Functions");
    tcase_add_test(tc_core, test_create_circular_list);
    tcase_add_test(tc_core, test_append_and_length);
    tcase_add_test(tc_core, test_get);
    tcase_add_test(tc_core, test_remove_at);
    tcase_add_test(tc_core, test_print);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(circular_linked_list_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

