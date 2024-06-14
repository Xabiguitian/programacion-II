/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include "dynamic_list.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


/*
Objetivo: Crea una lista vacía.
 Entrada: puntero lista
 Salida: tList list vacía
 Postcondiciones: La lista queda inicializada y no contiene elementos.
 */
void createEmptyList(tList *list) {
    *list = LNULL;
}

/*
Objetivo: Determina si la lista está vacía.
 Entrada: list a evaluar
 Salida: true si está vacía, false si no lo está
 Precondición: La lista debe estar previamente inicializada.
 */
bool isEmptyList(tList list) {
    return list == LNULL;
}

/*
 Objetivo: Crea un nodo cacio usando la memoria necesaria
 Entrada: tPos *pos
 Salida: El nodo creado vacío
 */
bool createNode(tPosL *pos) {
    *pos = malloc(sizeof(struct tNode));
    return *pos != LNULL;
}

/*
 Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de usuario se corresponda con el indicado (o LNULL si no existe tal elemento).
 Entrada: nombre de usuario a encontrar y lista
 Salida: posición del elemento solicitado o LNULL si no existe
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL findItem(tUserName username, tList list) {
    for (tPosL pos = list; pos != LNULL; pos = pos->next) {
        if (strcmp(pos->data.userName, username) == 0) {
            return pos;
        }
    }
    return LNULL;
}

/*
 Objetivo: Devuelve el contenido del elemento que ocupa la posición indicada.
 Entrada: posición del elemento y lista
 Salida: item de la posición indicada
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tItemL getItem(tPosL pos, tList list) {
    return pos->data;
}

/*
 Objetivo: Modifica el contenido del elemento situado en la posición indicada.
 Entrada: item nuevo que se quiere poner, posición del elemento a actualizar y puntero a lista
 Salida: lista con el elemento actualizado
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 Postcondición: El orden de los elementos de la lista no se ve modificado.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    pos->data = item;
}

/*
Objetivo: Devuelve la posición del primer elemento de la lista.
 Entrada: list
 Salida: posición del primer elemento
 Precondición: La lista no está vacía.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL first(tList list) {
    return list;
}

/*
Objetivo: Devuelve la posición del primer elemento de la lista.
 Entrada: lista
 Salida: posición del primer elemento
 Precondición: La lista no está vacía.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL last(tList list) {
    if (isEmptyList(list)) {
        return LNULL;
    }
    tPosL pos;
    for (pos = list; pos->next != LNULL; pos = pos->next);
    return pos;
}

/*
 Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 Entrada: posición y lista
 Salida: posición del siguiente elemento
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL next(tPosL pos, tList list) {
    return pos->next;
}

/*
 Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
 Entrada: posición y lista
 Salida: posición del anterior elemento
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL previous(tPosL pos, tList list) {
    if (pos == list) {
        return LNULL;
    }
    tPosL posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}

/*
 Objetivo: Inserta un elemento en la lista de forma ordenada en base al campo userName.
 Entrada: item a insertar y puntero a lista
 Salida: Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 Precondición: La lista debe estar previamente inicializada.
 Postcondición: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
 */
bool insertItem(tItemL item, tList *list) {
    tPosL posInsert;
    if (!createNode(&posInsert)) {
        return false;
    }

    posInsert->data = item;
    posInsert->next = LNULL;

    if (*list == LNULL) {
        *list = posInsert;
        return true;
    }

    if (findItem(item.userName, *list) != LNULL) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    tPosL prev = LNULL;
    tPosL current = *list;
    while (current != LNULL && strcmp(item.userName, current->data.userName) > 0) {
        prev = current;
        current = current->next;
    }
    if (prev == LNULL) {
        posInsert->next = *list;
        *list = posInsert;
    } else {
        posInsert->next = current;
        prev->next = posInsert;
    }

    return true;
}

/*
 Objetivo: Elimina de la lista el elemento que ocupa la posición indicada.
 Entrada: posición del elemento que se quiere eliminar y puntero a lista
 Salida: lista sin el elemento
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 Postcondición: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
 */
void deleteAtPosition(tPosL pos, tList *list) {
    if (isEmptyList(*list)) return;

    if (findItem(pos->data.userName, *list) == LNULL) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == LNULL) {
        tPosL prev = previous(pos, *list);
        prev->next = LNULL;
        free(pos);
    } else {
        tPosL q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}