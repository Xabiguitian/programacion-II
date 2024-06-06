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
#include <stdio.h>


void createEmptyList(tList *list) {

    *list = LNULL;
}

bool isEmptyList(tList list) {

    return list == LNULL; // Devuelve true si la lista está vacía
}

bool createNode(tPosL *pos) {

    *pos = malloc(sizeof(struct tNode));

    return *pos != LNULL;
}

tPosL numUsers(tList list){
    tPosL count = 0;
    for (tPosL pos = list; pos != LNULL; pos = pos->next) {
        count++;
    }
    return count;
}

tPosL findItem(tUserName username, tList list) {
    if (isEmptyList(list)){
        return LNULL;
    }else {

        for (tPosL pos = list; pos != LNULL; pos = pos->next) {
            if (pos->data.userName == username){
                return pos;
            }
        }
        return LNULL; // No se encontró el usuario, devuelve LNULL
    }
}

tItemL getItem(tPosL pos, tList list) {
    return pos->data;
}

void updateItem(tItemL item, tPosL pos, tList *list) {
    pos->data = item;
}

tPosL first(tList list) {
    if (isEmptyList(list) == true) {
        return LNULL; // Lista vacía
    }
    return 0; // Primera posición
}

tPosL last(tList list) {
    if (isEmptyList(list)) {
        return LNULL; // Lista vacía
    }

    return numUsers(list); // Última posición
}

tPosL next(tPosL pos,tList list) {
    return pos->next; // Siguiente posición
}

tPosL previous(tPosL pos,tList list) {
    if (pos == list){
        return LNULL;
    }else{
        tPosL posPrev;
        for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
        return posPrev; // Posición anterior
    }
}

bool insertItem(tItemL item, tList *list) {

    if (numUsers(*list) >= MAX_USERS) return false;
    if (isEmptyList(*list) == true) return false;

    tPosL posInsert,pos;

    if (!createNode(&pos)) return false;
    pos = *list;

    if (!createNode(&posInsert)) return false;
    posInsert->data = item;

    if (isEmptyList(*list)) {

        *list = posInsert;
        return true;
    }

    int count=0;
    for (int i = 0; i < numUsers(*list); i++) {
        if(strcmp(item.userName,pos->data.userName) < 0 ){

            pos = pos->next;
            count++;

        }else{
            for (int i = count; i < numUsers(*list); i++){
                pos->next = pos;
            }
            *list = pos;
            for (int i = count; i >= 0; i--){
                *list = (*list)->next;
            }
            *list = (*list)->next;
            (*list)->data = item;
        }
    }

    return true;
}

void deleteAtPosition(tPosL pos,tList *list) {
    if (isEmptyList(*list)) return;// Lista vacía, no se puede eliminar

    if (pos < 0 || pos >= numUsers(*list)) return; // Posición inválida

    if (numUsers(*list) == 1) {
        *list = LNULL;
        return;
    }

    if (next(pos, *list) == LNULL) {
        previous(pos, *list)->next = LNULL;
        return;
    }


    for (tPosL i = 0; i < pos; i++){
        *list = (*list)->next;
    }

    // Desplazar los elementos hacia atrás para eliminar el elemento en la posición indicada
    for (tPosL i = numUsers(*list)-1; i > pos; i++) {
        previous(pos, *list) = *list;
    }
}