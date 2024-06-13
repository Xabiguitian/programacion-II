/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#include "types.h"
#include "user_list.h"
#include <string.h>
#include <stdbool.h>

void createEmptyListU(tListU *list) {
    list->numUsers = 0; // Inicializa el número de usuarios en 0
}

bool isEmptyListU(struct tListU list) {
    return list.numUsers == 0; // Devuelve true si la lista está vacía
}

tItemU getItemU(tPosU pos,struct tListU list) {
    return list.userList[pos]; //Busca el usuario en la posición indicada
}

void updateItemU(tItemU item, tPosU pos,struct tListU *list) {
    list->userList[pos] = item; //Reemplaza el elemento en la posición indicada
}

tPosU firstU(struct tListU list) {
    if (isEmptyListU(list)) {
        return NULLU; // Lista vacía
    }
    return 0; // Primera posición
}

tPosU lastU(struct tListU list) {
    if (isEmptyListU(list)) {
        return NULLU; // Lista vacía
    }
    return list.numUsers - 1; // Última posición
}

tPosU nextU(tPosU pos,tListU list) {
    if (pos < 0 || pos >= list.numUsers - 1) {
        return NULLU; // Posición inválida o última posición
    }
    return pos + 1; // Siguiente posición
}

tPosU previousU(tPosU pos,tListU list) {
    if (pos <= 0 || pos >= list.numUsers) {
        return NULLU; // Posición inválida o primera posición
    }
    return pos - 1; // Posición anterior
}




tPosU findItemU(tUserName username, tListU list) {
    for (int i = 0; i < list.numUsers; i++) {
        if (strcmp(list.userList[i].userName, username) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }
    }
    return NULLU; // No se encontró el usuario, devuelve LNULLU
}

bool insertItemU(tItemU item, tListU *list) {
    // Verifica si la lista está llena
    if (list->numUsers >= MAX_USERS) {
        // La lista está llena, no se puede insertar más usuarios
        return false;
    }

    // Verifica si el usuario ya existe en la lista
    if (findItemU(item.userName, *list) == NULLU) {
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


void deleteAtPositionU(tPosU pos, tListU *list) {
    // Verifica si la posición está fuera de los límites de la lista
    if (pos < 0 || pos >= list->numUsers) {
        // La posición está fuera de los límites, no se puede eliminar ningún usuario
        return;
    }

    // Verifica si el usuario en la posición especificada tiene alguna canción en su lista de reproducción
    if (list->userList[pos].songList.numSongs != 0) {
        // El usuario tiene canciones en su lista de reproducción, no se puede eliminar
        return;
    }

    // Si el usuario a eliminar está en la última posición de la lista
    if (pos == list->numUsers - 1) {
        // Elimina el usuario estableciendo su nombre de usuario como una cadena vacía
        strcpy(list->userList[pos].userName, "");
        // Reinicia el tiempo total de reproducción del usuario a 0
        list->userList[pos].totalPlayTime = 0;

    } else {
        // Si el usuario a eliminar no está en la última posición

        // Desplaza los usuarios a la izquierda para llenar el espacio del usuario eliminado
        for (int i = pos; i < list->numUsers; i++) {
            list->userList[i] = list->userList[i + 1];
        }
    }

    // Decrementa el número de usuarios en la lista
    list->numUsers--;
}