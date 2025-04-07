#include "circular_linked_list.h"

#define CIRCULAR_LINKED_LIST_IMPLEMENTATION
IMPLEMENT_CIRCULAR_LINKED_LIST(int)

void print_int(int value) {
    printf("%d", value);
}

int main() {
    // Crear la lista circular
    CircularList_int* lista = circular_list_int_create();

    // Agregar elementos a la lista
    circular_list_int_append(lista, 10);
    circular_list_int_append(lista, 20);
    circular_list_int_append(lista, 30);
    circular_list_int_append(lista, 40);

    printf("Lista circular después de insertar 4 elementos:\n");
    circular_list_int_print(lista, print_int); // Imprimir la lista

    int valor;
    if (circular_list_int_get(lista, 2, &valor)) { // Obtener valor en la posición 2
        printf("Elemento en la posición 2: %d\n", valor);
    }

    circular_list_int_remove_at(lista, 1); // Eliminar elemento en la posición 1
    printf("Lista después de eliminar el elemento en la posición 1:\n");
    circular_list_int_print(lista, print_int); // Imprimir la lista después de la eliminación

    circular_list_int_destroy(lista); // Liberar la memoria de la lista
    return 0;
}


