#include <stdio.h>
#include <string.h>
#include "static_list.h"
#include "static_list.c"
#include "types.h"



int main () {
    char list[tamanolista];
    createEmptyList(list);
    printf("%d", isEmptyList(list, sizeof(list)));
    printf("\nLa posicion del primer elemento es %d", first(list));
    printf("\nLa posicion del último elemento es %d", last(list));
    next(1, list);
    previous(1,list);
    insertItem(tItemL(strcpy(tItemL[0].username, "Lucas")));
}