#include <stdio.h>
#include "static_list.h"

int main() {
    tList list = createEmptyList();


    createEmptyList();
    printf("%d", isEmptyList(list, sizeof(list)));
    printf("\nLa posicion del primer elemento es %d", first(list));
    printf("\nLa posicion del ultimo elemento es %d", last(list));
    next(1, list);
    previous(1,list);
    insertItem(7,2,list);
    deleteAtPosition(1, list);
    printf("\nEl contenido del elemento en la posicion 2 es: %d", getItem(2, list));

    return 0;
}
