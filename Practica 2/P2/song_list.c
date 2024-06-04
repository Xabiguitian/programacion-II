/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#include "types.h"
#include "song_list.h"
#include <string.h>
#include <stdbool.h>


void createEmptyListS (tListS *list) {
    list->numSongs = 0; // Inicializa el número de usuarios en 0
}

bool isEmptyListS (tListS list) {
    return list.numSongs == 0; // Devuelve true si la lista está vacía
}

tPosS firstS (tListS list) {
    if (isEmptyListS(list)) {
        return NULLS; // Lista vacía
    }
    return 0; // Primera posición
}

tPosS lastS (tListS list) {
    if (isEmptyListS (list)) {
        return NULLS; // Lista vacía
    }
    return list.numSongs - 1; // Última posición
}

tPosS nextS (tPosS pos,tListS list) {
    if (pos < 0 || pos >= MAX_LIST_LENGTH || pos >= list.numSongs) {
        return NULLU; // Posición inválida o última posición
    }
    return pos + 1; // Siguiente posición
}

tPosS previousS (tPosS pos,tListS list) {
    if (pos <= 0 || pos > MAX_LIST_LENGTH || pos >= list.numSongs) {
        return NULLU; // Posición inválida o primera posición
    }
    return pos - 1; // Posición anterior
}

bool insertItemS (tItemS item, tPosS pos, tListS *list) {
    if (list->numSongs >= MAX_LIST_LENGTH) {
        // La lista está llena
        return false;
    }

    if (pos == NULLS){
        list->songList[lastS(*list)+1].playTime = item.playTime;
        strcpy(list->songList[lastS(*list)+1].songTitle, item.songTitle);
        list->numSongs++; // Incrementar el número de usuarios
        return true;
    }

    // Desplazar los elementos hacia adelante para hacer espacio para el nuevo elemento
    for (int i = list->numSongs; i > pos; i--) {
        list->songList[i] = list->songList[i - 1];
    }

    // Insertar el nuevo elemento en la posición indicada
    list->songList[pos].playTime = item.playTime;
    strcpy(list->songList[pos].songTitle, item.songTitle);
    list->numSongs++; // Incrementar el número de usuarios
    return true;
}

void deleteAtPositionS(tPosS pos,tListS *list) {
    if (isEmptyListS(*list)) {
        // Lista vacía, no se puede eliminar
        return;
    }

    if (pos < 0 || pos >= list->numSongs) {
        // Posición inválida
        return;
    }

    // Desplazar los elementos hacia atrás para eliminar el elemento en la posición indicada
    for (int i = pos; i < list->numSongs - 1; i++) {
        list->songList[i] = list->songList[i + 1];
    }

    list->numSongs--; // Decrementar el número de usuarios
}

tItemS getItemS (tPosS pos,tListS list) {
    return list.songList[pos]; //Develve el elemento de la posición indicada
}

void updateItemS (tItemS item, tPosS pos, tListS *list) {
    list->songList[pos] = item; //Cambia el elemento de la lista en la posición indicada por el item seleccionado
}

tPosS findItemS (tSongTitle songtitle, tListS list) {
    for (int i = 0; i < list.numSongs; i++) {
        if (strcmp(list.songList[i].songTitle, songtitle) == 0) {
            return i; // Se encontró el usuario, devuelve la posición
        }
    }
    return NULLS; // No se encontró el usuario, devuelve NULLS
}