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

tPosL findItem(tUserName username, tList list) {
    for (int i = 0; i < list.numUsers; i++) {
        if (strcmp(list.userList[i].userName, username) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }else if(strcmp(list.userList[i].userName, username) > 0){
            return LNULL; // Devuelve nulo si ya se pasó la posición en la que debería estar el usuario (así no sigue buscando en la lista y optimizamos el código)
        }
    }
    return LNULL; // No se encontró el usuario, devuelve LNULL
}

bool insertItem(struct tItemL item, tList *list) {
    // Verifica si la lista está llena
    if (list->numUsers >= MAX_USERS) {
        // La lista está llena, no se puede insertar más usuarios
        return false;
    }

    // Verifica si el usuario ya existe en la lista
    if (findItem(item.userName, *list) == LNULL) {
        // El usuario no existe en la lista

        // Si la lista está vacía, inserta el usuario en la primera posición
        if (list->numUsers == 0) {
            list->userList[0] = item;
            list->numUsers++;
            return true;
        } else {
            // La lista no está vacía, busca la posición correcta para insertar el usuario

            for (int i = 0; i < list->numUsers; i++) {
                // Compara los nombres de usuario para encontrar la posición correcta
                if (strcmp(item.userName, list->userList[i].userName) == 0) {
                    // El nombre de usuario ya existe en la lista, no se puede insertar
                    return false;
                } else if (strcmp(item.userName, list->userList[i].userName) < 0) {
                    // Se encontró la posición correcta para insertar el usuario

                    // Desplaza los usuarios a la derecha para hacer espacio para el nuevo usuario
                    for (int j = list->numUsers; j >= i; j--) {
                        list->userList[j] = list->userList[j - 1];
                    }

                    // Inserta el nuevo usuario en la posición correcta
                    list->userList[i] = item;
                    list->numUsers++;
                    return true;
                }
            }

            // Si no se encontró la posición correcta, inserta el usuario al final de la lista
            list->userList[list->numUsers] = item;
            list->numUsers++;
            return true;
        }
    } else {
        // El usuario ya existe en la lista, no se puede insertar
        return false;
    }
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