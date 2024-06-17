/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include "user_list.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


/* Objetivo: crear una lista vacia e inicializada
 * Salida: la lista vacia
 * Postcondición: la lista según el tipo de dato que tenga */
void createEmptyListU(tListU *list) {
    *list = NULLU;
}

/*:Objetivo: Comprobar que la lista esté vacia
 * Salida: La lista a comprobar, tListU list
 * Postcondición: Si la lista está vacia devuelve TRUE, si no FALSE
 */
bool isEmptyListU(tListU list) {
    return list == NULLU;
}


/* Objetivo: Crea un nodo vacio usando la memoria necesaria.
 * Entrada: tPosS *pos, una posición valida.
 * Salida: El nodo vacio
 */
bool createNodeU(tPosU *pos) {
    *pos = malloc(sizeof(struct tNodeU));
    return *pos != NULLU;
}

/* Objetivo: Busca el elemento en la lista por el nombre de usuario
 * Entrada: El nombre de usuario tUserName username que se quiere buscar,
 * y la lista tListU list en la cual se quiere buscar.
 * Salida: La posición del elemento que se quiere buscar, si no devuelve NULLU
 */
tPosU findItemU(tUserName username, tListU list) {
    for (tPosU pos = list; pos != NULLU; pos = pos->next) {
        if (strcmp(pos->data.userName, username) == 0) {
            return pos;
        }
    }
    return NULLU;
}


/* Objetivo: Devolver el contenido de un elemento de la lista
 * Entrada: tPosU pos, la cual determina la posición del elemento, y
 * tListU list, que inkdica la lista que se analiza.
 * Salida: La lista modificada en el elemento indicado
 * Precondición: tPosU pos es un elemento válido en la lista
 */
tItemU getItemU(tPosU pos, tListU list) {
    return pos->data;
}


/* Objetivo: Modifica el contenido de un elemento de la lista.
 * Entrada:tItemU item, es el contenido que vamos a asignar, tPosU pos, la posicíon del elemento a cambiar,
 * tListU *list, la lista a analizar.
 * Salida: La lista con el elemento modificado.
 * Precondición: tPosU pos, es una posición valida de la lista.
 */
void updateItemU(tItemU item, tPosU pos, tListU *list) {
    pos->data = item;
}


/* Objetivo: Devuelve la posición del primer elemento de la lista.
 * Entrada: tListU list, la lista a analizar.
 * Salida: La posición del primer elemento.
 * Precondición:La lista no está vacia.
 */
tPosU firstU(tListU list) {
    return list;
}

/* Objetivo: Devuelve la posición del último elemento de la lista.
 * Entrada: tListU list, la lista a analizar para encontrar la última posición,
 * Salida: La posición del último elemento.
 * Precondición: La lista no está vacia.
 */
tPosU lastU(tListU list) {
    if (isEmptyListU(list)) {
        return NULLU;
    }
    tPosU pos;
    for (pos = list; pos->next != NULLU; pos = pos->next);
    return pos;
}

/* Objetivo: Devuelve la posición del próximo elemento.
 * Entrada: tPosU pos, la posición del elemento actual.
 * Salida: La posición del próximo elemento.
 * Precondición: La lista no está vacia.
 */
tPosU nextU(tPosU pos, tListU list) {
    return pos->next;
}


/* Objetivo: Devolver la posición del elemento anterior.
 * Entrada: tPosU pos, la posición del delemento actual, tListU list, la lista a analizar.
 * Salida: La posición del elemento anterior.
 * Precondición: tPosU pos es una posición válida.
 */
tPosU previousU(tPosU pos, tListU list) {
    if (pos == list) {
        return NULLU;
    }
    tPosU posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}



/* Objetivo: Cuando la  posición es nula añade un elemento al final de la lista,
 * si no el elemento queda antes de la posición indicada.
 * Entrada: tItemU item, es el elemento a insertar, tListU *list, la lista a analizar,
 * tPosU posInsert, es la posición indicada.
 * Salida: Si lo ha conseguido insertar devuelve TRUE si no FALSE.
 * Precondición: tPosU posInsert, es un elemento válido o nulo.
 * Postcondición: Puede que la posición de los elementos de la lista haya variado.
 */
bool insertItemU(tItemU item, tListU *list) {
    tPosU posInsert;
    if (!createNodeU(&posInsert)) {
        return false;
    }

    posInsert->data = item;
    posInsert->next = NULLU;

    if (*list == NULLU) {
        *list = posInsert;
        return true;
    }

    if (findItemU(item.userName, *list) != NULLU) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    tPosU prev = NULLU;
    tPosU current = *list;
    while (current != NULLU && strcmp(item.userName, current->data.userName) > 0) {
        prev = current;
        current = current->next;
    }
    if (prev == NULLU) {
        posInsert->next = *list;
        *list = posInsert;
    } else {
        posInsert->next = current;
        prev->next = posInsert;
    }

    return true;
}


/* Objetivo: Elimina el elemento de la posición indicada.
 * Entrada: tPosU pos, la posición del elemento, tListU *list, la lista a recorrer.
 * Salida: La lista sin el elemento.
 * Precondición: tPosU pos, es una opsición valida.
 * Postcondición: Las posiciones de los elementos pudieron variar.
 */
void deleteAtPositionU(tPosU pos, tListU *list) {
    if (isEmptyListU(*list)) return;

    if (findItemU(pos->data.userName, *list) == NULLU) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == NULLU) {
        tPosU prev = previousU(pos, *list);
        prev->next = NULLU;
        free(pos);
    } else {
        tPosU q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}