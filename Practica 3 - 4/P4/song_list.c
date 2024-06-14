/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include "song_list.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


/* Objetivo: Crear una lista vacia e inicializada.
 * Salida: La lista vacia.
 * Postcondición: La lista sin ningún dato.
 */
void createEmptyListS(tListS *list) {
    *list = NULLS;
}


/* Objetivo: Comprobar que la lista está vacia.
 * Entrada: tListS list, es la lista a comprobar.
 * Salida: Si la lista está vacia devuelve TRUE si no FALSE.
 */
bool isEmptyListS(tListS list) {
    return list == NULLS;
}


/* Objetivo: Crea un nodo vacio usando la memoria necesaria.
 * Entrada: tPosS *pos, una posición valida.
 * Salida: El nodo vacio
 */
bool createNodeS(tPosS *pos) {
    *pos = malloc(sizeof(struct tNodeS));
    return *pos != NULLS;
}


/* Objetivo: Buscar el elemento correspondiente al nombre de usuario en la lista.
 * Entrada: tUserName username, el elemento a buscar, tListS list, la lista en la que buscar.
 * Salida: La posición del elemento indicado,  si no NULLS
 */
tPosS findItemS(tUserName username, tListS list) {
    for (tPosS pos = list; pos != NULLS; pos = pos->next) {
        if (strcmp(pos->data.songTitle, username) == 0) {
            return pos;
        }
    }
    return NULLS;
}



/* Objetivo: Devuelve un elemento de la lista
 * Entrada: tPosS pos, una posición valida de la lista, tListS list, la lista a buscar.
 * Salida: El contenido en la lista de la posición indicada.
 */
tItemS getItemS(tPosS pos, tListS list) {
    return pos->data;
}


/* Objetivo: Modifica un elemento de la lista.
 * Entrada: tItemS item, el nuevo elemento a implementar, tPosS pos, una posición valida en la lista,
 * tListS *list, la lista en la que buscar.
 * Salida: La lista modificada.
 * Precodición: tPosS pos, es una posición válida en la lista.
 */
void updateItemS(tItemS item, tPosS pos, tListS *list) {
    pos->data = item;
}


/* Objetivo: Devuelve la posición del primer elemento de la lista.
 * Entrada: tListS list, la lista a analizar.
 * Salida: La posición del primer elemento.
 * Precondición: La lista no está vacia.
 */
tPosS firstS(tListS list) {
    return list;
}



/* Objetivo: Devuelve la posición del último elemento de la lista.
 * Entrada: tListS list, la lista a analizar.
 * Salida: La posición del último elemento.
 * Precondición: La lista no está vacia.
 */
tPosS lastS(tListS list) {
    if (isEmptyListS(list)) {
        return NULLS;
    }
    tPosS pos;
    for (pos = list; pos->next != NULLS; pos = pos->next);
    return pos;
}

tPosS nextS(tPosS pos, tListS list) {
    return pos->next;
}

tPosS previousS(tPosS pos, tListS list) {
    if (pos == list) {
        return NULLS;
    }
    tPosS posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}



/* Objetivo: Si la posición es nula, añade un elemento al final de la lista,
 * si no el elemento qeudará insertado antes.
 * Entrada: tPosS posInsert, que determina la posición del elemento, tListS *list, la lista a analizar,
 * tItemS item, es el elemento a insertar.
 * Salida: La lista devuelve TRUE si ha podido insertarlo y FALSE si no lo consigue.
 * Precondición: tPosS posInsert, es una posición válida o nula.
 * Postcondición: Las posiciones de los elementos de la lista han podido variar.
 */
bool insertItemS(tItemS item, tListS *list) {
    tPosS posInsert;
    if (!createNodeS(&posInsert)) {
        return false;
    }

    if (findItemS(item.songTitle, *list) != NULLS) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    posInsert->data = item;
    posInsert->next = NULLS;

    if (*list == NULLS) {
        *list = posInsert;
        return true;
    }


    tPosS prev = NULLS;
    tPosS current = *list;
    while (current != NULLS && strcmp(item.songTitle, current->data.songTitle) > 0) {
        prev = current;
        current = current->next;
    }
    if (prev == NULLS) {
        posInsert->next = *list;
        *list = posInsert;
    } else {
        posInsert->next = current;
        prev->next = posInsert;
    }

    return true;
}



/* Objetivo: Elimina el elemento de una posición.
 * Entrada: tPosS pos, una posición  valida de la lista, tListS *list, es la lista a analizar.
 * Salida:La lista sin el elemento.
 * Precondición: tPosS es una posición valida en la lista.
 * Postcondición: Las posiciones de los elementos de la lista han podido variar.
 */
void deleteAtPositionS(tPosS pos, tListS *list) {
    if (isEmptyListS(*list)) return;

    if (findItemS(pos->data.songTitle, *list) == NULLS) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == NULLS) {
        tPosS prev = previousS(pos, *list);
        prev->next = NULLS;
        free(pos);
    } else {
        tPosS q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}