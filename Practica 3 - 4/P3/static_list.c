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

//Crea una lista vacía
void createEmptyList(tList *list) {
    list->lastPos = LNULL;
}

// comprueba si la lista está vacía
bool isEmptyList(tList list) {
    return list.lastPos == LNULL;
}

// Devuelve la posición del primer usuario en la lista, o LNULL si está vacía
tPosL first(tList list) {
    return isEmptyList(list) ? LNULL : 0;
}

//Devuelve la posición del último usuario en la lista, o LNULL si está vacía
tPosL last(tList list) {
    return list.lastPos;
}

// Devuelve la posición del siguiente usuario después de la posición dada
tPosL next(tPosL pos, tList list) {
    if(pos >= list.lastPos || pos < 0){
        return LNULL;
    }
    return pos++;
}

//Devuelve la posición del usuario anterior a la posición dada
tPosL previous(tPosL pos, tList list) {
    if(pos > list.lastPos || pos <= 0){
        return LNULL;
    }
    return pos--;
}

//Inserta  un nuevo usuario en la posición dada
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

// Elimina el usuario en la posición dada
void deleteAtPosition(tPosL pos, tList *list) {
    if (pos < 0 || pos >= numUsers(*list)) {
        return; // Invalid position
    }

    for (int i = pos; i < list->lastPos; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->lastPos--;
}

// Devuelve el usuario en la posición dada
tItemL getItem(tPosL pos, tList list) {
    return list.data[pos];
}

// actualiza el usuario en la posición dada con el nuevo valor proporcionado
void updateItem(tItemL item, tPosL pos, tList *list) {
    if (pos < 0 || pos > list->lastPos){
        return;
    }
    list->data[pos] = item;
}

//Busca un usuario por nombre de usuario y devuelve su posición en la lista
tPosL findItem(tUserName username, tList list) {
    for (int i = 0; i < numUsers(list); i++) {
        if (strcmp(list.data[i].userName, username) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }
    }
    return LNULL; // No se encontró el usuario, devuelve LNULL
}


