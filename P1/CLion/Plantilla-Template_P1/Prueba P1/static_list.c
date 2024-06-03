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

//Crea una lista vacía
tList createEmptyList() {
    tList list;
    list.numUsers = 0;
    return list;
}

// comprueba si la lista está vacía
bool isEmptyList(tList list) {
    return list.numUsers == 0;
}

// Devuelve la posición del primer usuario en la lista, o LNULL si está vacía
tPosL first(tList list) {
    return isEmptyList(list) ? LNULL : 0;
}

//Devuelve la posición del último usuario en la lista, o LNULL si está vacía
tPosL last(tList list) {
    return isEmptyList(list) ? LNULL : list.numUsers - 1;
}

// Devuelve la posición del siguiente usuario después de la posición dada
tPosL next(tPosL p, tList list) {
    return (p < list.numUsers - 1) ? p + 1 : LNULL;
}

//Devuelve la posición del usuario anterior a la posición dada
tPosL previous(tPosL p, tList list) {
    return (p > 0) ? p - 1 : LNULL;
}

//Inserta  un nuevo usuario en la posición dada
bool insertItem(tItemL item, tPosL p, tList *list) {
    if (list->numUsers >= MAX_USERS) {
        return false; // List full
    }

    if (p == LNULL) {
        p = list->numUsers;
    }

    for (int i = list->numUsers; i > p; i--) {
        list->userList[i] = list->userList[i - 1];
    }

    list->userList[p] = item;
    list->numUsers++;
    return true;
}

// Elimina el usuario en la posición dada
void deleteAtPosition(tPosL p, tList *list) {
    if (p < 0 || p >= list->numUsers) {
        return; // Invalid position
    }

    for (int i = p; i < list->numUsers - 1; i++) {
        list->userList[i] = list->userList[i + 1];
    }

    list->numUsers--;
}

// Devuelve el usuario en la posición dada
tItemL getItem(tPosL p, tList list) {
    return list.userList[p];
}

// actualiza el usuario en la posición dada con el nuevo valor proporcionado
void updateItem(tItemL item, tPosL p, tList *list) {
    if (p < 0 || p >= list->numUsers) {
        return; // Invalid position
    }

    list->userList[p] = item;
}

//Busca un usuario por nombre de usuario y devuelve su posición en la lista
tPosL findItem(tUserName username, tList list) {
    for (int i = 0; i < list.numUsers; i++) {
        if (strcmp(list.userList[i].userName, username) == 0) {
            return i;
        }
    }
    return LNULL;
}
