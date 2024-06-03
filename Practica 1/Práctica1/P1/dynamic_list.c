/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include <string.h>
#include <stdbool.h>


void createEmptyList(tList *list) {
    list->numUsers = 0; // Inicializa el número de usuarios en 0
}

bool isEmptyList(struct tList list) {
    return list.numUsers == 0; // Devuelve true si la lista está vacía
}

bool insertItem(struct tItemL item, tPosL pos, tList *list) {
    if (list->numUsers >= MAX_USERS) {
        // La lista está llena
        return false;
    }

    if (pos < 0 || pos > list->numUsers) {
        // Posición inválida
        return false;
    }

    // Desplazar los elementos hacia adelante para hacer espacio para el nuevo elemento
    for (int i = list->numUsers; i > pos; i--) {
        list->userList[i] = list->userList[i - 1];
    }

    // Insertar el nuevo elemento en la posición indicada
    list->userList[pos] = item;
    list->numUsers++; // Incrementar el número de usuarios
    return true;
}

void deleteAtPosition(tPosL pos,tList *list) {
    if (isEmptyList(*list)) {
        // Lista vacía, no se puede eliminar
        return;
    }

    if (pos < 0 || pos >= list->numUsers) {
        // Posición inválida
        return;
    }

    // Desplazar los elementos hacia atrás para eliminar el elemento en la posición indicada
    for (int i = pos; i < list->numUsers - 1; i++) {
        list->userList[i] = list->userList[i + 1];
    }

    list->numUsers--; // Decrementar el número de usuarios
}

tItemL getItem(tPosL pos,struct tList list) {
    return list.userList[pos];
}

void updateItem(tItemL item, tPosL pos,struct tList *list) {
    list->userList[pos] = item;
}

tPosL findItem(tUserName username, tList list) {
    for (int i = 0; i < list.numUsers; i++) {
        if (strcmp(list.userList[i].userName, username) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }
    }
    return LNULL; // No se encontró el usuario, devuelve LNULL
}

tPosL first(struct tList list) {
    if (isEmptyList(list)) {
        return LNULL; // Lista vacía
    }
    return 0; // Primera posición
}

tPosL last(struct tList list) {
    if (isEmptyList(list)) {
        return LNULL; // Lista vacía
    }
    return list.numUsers - 1; // Última posición
}

tPosL next(tPosL pos,tList list) {
    if (pos < 0 || pos >= list.numUsers - 1) {
        return LNULL; // Posición inválida o última posición
    }
    return pos + 1; // Siguiente posición
}

tPosL previous(tPosL pos,tList list) {
    if (pos <= 0 || pos >= list.numUsers) {
        return LNULL; // Posición inválida o primera posición
    }
    return pos - 1; // Posición anterior
}