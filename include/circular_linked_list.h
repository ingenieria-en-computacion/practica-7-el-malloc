#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_CIRCULAR_LINKED_LIST(TYPE) \
    typedef struct NodeCircular_##TYPE { \
        TYPE data; \
        struct NodeCircular_##TYPE* next; \
    } NodeCircular_##TYPE; \
    \
    NodeCircular_##TYPE* node_circular_##TYPE##_create(TYPE data); \
    \
    typedef struct { \
        NodeCircular_##TYPE* tail; \
        size_t length; \
    } CircularList_##TYPE; \
    \
    CircularList_##TYPE* circular_list_##TYPE##_create(void); \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list); \
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data); \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos); \
    bool circular_list_##TYPE##_get(const CircularList_##TYPE* list, size_t pos, TYPE* out); \
    void circular_list_##TYPE##_print(const CircularList_##TYPE* list, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_CIRCULAR_LINKED_LIST(TYPE) \
    NodeCircular_##TYPE* node_circular_##TYPE##_create(TYPE data) { \
        NodeCircular_##TYPE* node = malloc(sizeof(NodeCircular_##TYPE)); \
        if (!node) return NULL; \
        node->data = data; \
        node->next = NULL; \
        return node; \
    } \
    \
    CircularList_##TYPE* circular_list_##TYPE##_create(void) { \
        CircularList_##TYPE* list = malloc(sizeof(CircularList_##TYPE)); \
        if (!list) return NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list) { \
        if (!list || !list->tail) return; \
        NodeCircular_##TYPE* current = list->tail->next; \
        NodeCircular_##TYPE* temp; \
        do { \
            temp = current; \
            current = current->next; \
            free(temp); \
        } while (current != list->tail->next); \
        free(list); \
    } \
    \
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        NodeCircular_##TYPE* new_node = node_circular_##TYPE##_create(data); \
        if (!new_node) return false; \
        if (!list->tail) { \
            list->tail = new_node; \
            new_node->next = new_node; \
        } else { \
            new_node->next = list->tail->next; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos) { \
        if (!list || !list->tail || pos >= list->length) return false; \
        NodeCircular_##TYPE *prev = list->tail, *current = list->tail->next; \
        for (size_t i = 0; i < pos; ++i) { \
            prev = current; \
            current = current->next; \
        } \
        if (current == list->tail) list->tail = (list->length == 1) ? NULL : prev; \
        if (prev == current) list->tail = NULL; \
        else prev->next = current->next; \
        free(current); \
        list->length--; \
        return true; \
    } \
    \
    bool circular_list_##TYPE##_get(const CircularList_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !list->tail || pos >= list->length || !out) return false; \
        NodeCircular_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        *out = current->data; \
        return true; \
    } \
    \
    void circular_list_##TYPE##_print(const CircularList_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !list->tail || !print_fn) return; \
        NodeCircular_##TYPE* current = list->tail->next; \
        printf("["); \
        for (size_t i = 0; i < list->length; ++i) { \
            print_fn(current->data); \
            if (i < list->length - 1) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }

// ----------------------------
// Declaraciones para tipos concretos
// ----------------------------
DECLARE_CIRCULAR_LINKED_LIST(int)
DECLARE_CIRCULAR_LINKED_LIST(char)

// ----------------------------
// Implementaciones para tipos concretos
// ----------------------------
#ifdef CIRCULAR_LINKED_LIST_IMPLEMENTATION
IMPLEMENT_CIRCULAR_LINKED_LIST(int)
IMPLEMENT_CIRCULAR_LINKED_LIST(char)
#endif

