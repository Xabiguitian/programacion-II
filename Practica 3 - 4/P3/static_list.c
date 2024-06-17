/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "static_list.h"
#include "types.h"
#include <stdbool.h>
#include <string.h>

int numUsers(tList list){
    return list.lastPos +1;
}

/*
Objetivo: Crea una lista vacía.
 Entrada: puntero lista
 Salida: tList list vacía
 Postcondiciones: La lista queda inicializada y no contiene elementos.
 */
void createEmptyList(tList *list) {
    list->lastPos = LNULL;
}

/*
Objetivo: Determina si la lista está vacía.
 Entrada: list a evaluar
 Salida: true si está vacía, false si no lo está
 Precondición: La lista debe estar previamente inicializada.
 */
bool isEmptyList(tList list) {
    return list.lastPos == LNULL;
}

/*
Objetivo: Devuelve la posición del primer elemento de la lista.
 Entrada: list
 Salida: posición del primer elemento
 Precondición: La lista no está vacía.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL first(tList list) {
    return isEmptyList(list) ? LNULL : 0;
}

/*
Objetivo: Devuelve la posición del primer elemento de la lista.
 Entrada: lista
 Salida: posición del primer elemento
 Precondición: La lista no está vacía.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL last(tList list) {
    return isEmptyList(list) ? LNULL: list.lastPos;
}

/*
 Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 Entrada: posición y lista
 Salida: posición del siguiente elemento
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL next(tPosL pos, tList list) {
    if(pos >= list.lastPos || pos < 0){
        return LNULL;
    }
    return pos++;
}

/*
 Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
 Entrada: posición y lista
 Salida: posición del anterior elemento
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL previous(tPosL pos, tList list) {
    if(pos > list.lastPos || pos <= 0){
        return LNULL;
    }
    return pos--;
}

/*
 Objetivo: Inserta un elemento en la lista de forma ordenada en base al campo userName.
 Entrada: item a insertar y puntero a lista
 Salida: Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 Precondición: La lista debe estar previamente inicializada.
 Postcondición: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
 */
bool insertItem(tItemL item, tList *list) {
    if (numUsers(*list) >= MAX_USERS) {
        return false; // Lista llena
    }

    int i;
    for (i = numUsers(*list); i > 0 && strcmp(item.userName, list->data[i-1].userName) < 0; i--) {
        list->data[i] = list->data[i-1];
    }
    list->data[i] = item;
    list->lastPos++;
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
    if (pos < 0 || pos >= numUsers(*list)) {
        return; // Invalid position
    }

    for (int i = pos; i < list->lastPos; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->lastPos--;
}

/*
 Objetivo: Devuelve el contenido del elemento que ocupa la posición indicada.
 Entrada: posición del elemento y lista
 Salida: item de la posición indicada
 Precondición: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 */
tItemL getItem(tPosL pos, tList list) {
    return list.data[pos];
}

/*
 Objetivo: Modifica el contenido del elemento situado en la posición indicada.
 Entrada: item nuevo que se quiere poner, posición del elemento a actualizar y puntero a lista
 Salida: lista con el elemento actualizado
 Precondiciones: La posición indicada es una posición válida en la lista.
 Precondición: La lista debe estar previamente inicializada.
 Precondición: El orden de los elementos de la lista no se ve modificado.
 */
void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos < 0 || pos > list->lastPos){
        return;
    }
    list->data[pos] = item;
}

/*
 Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de usuario se corresponda con el indicado (o LNULL si no existe tal elemento).
 Entrada: nombre de usuario a encontrar y lista
 Salida: posición del elemento solicitado o LNULL si no existe
 Precondición: La lista debe estar previamente inicializada.
 */
tPosL findItem(tUserName username, tList list) {
    for (int i = 0; i < numUsers(list); i++) {
        if (strcmp(list.data[i].userName, username) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }
    }
    return LNULL; // No se encontró el usuario, devuelve LNULL
}


