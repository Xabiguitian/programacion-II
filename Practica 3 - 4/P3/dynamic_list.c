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


tList createEmptyList(tList *list) {

    *list = LNULL;
    return *list;
}

bool isEmptyList(tList list) {

    return list == LNULL; // Devuelve true si la lista está vacía
}

bool createNode(tPosL *pos) {

    *pos = malloc(sizeof(struct tNode));

    return *pos != LNULL;
}

int numUsers(tList list){
    int count = 0;
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

tList updateItem(tItemL item, tPosL pos, tList *list) {
    pos->data = item;
    return *list;
}

tPosL first(tList list) {
    if (isEmptyList(list) == true) {
        return LNULL; // Lista vacía
    }
    return list; // Primera posición
}

tPosL last(tList list) {
    if (isEmptyList(list)) {
        return LNULL; // Lista vacía
    }

    tPosL pos;
    for (pos = list; pos->next != LNULL; pos = pos->next);

    return pos; // Última posición
}

tPosL next(tPosL pos,tList list) {
    return (pos->next == LNULL)? LNULL : pos->next; // Siguiente posición a no la indicada ya sea la última, en ese caso devolvería LNULL
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

    tPosL posInsert,pos;

    if (!createNode(&pos)) return false;
    pos = *list;

    if (!createNode(&posInsert)) return false;
    posInsert->data = item;

    if (isEmptyList(*list) == true) {

        *list = posInsert;
        (*list)->next = LNULL;
        return true;
    }

    int count=0;
    for (int i = 0; i < numUsers(*list); i++) {
        if(strcmp(item.userName,pos->data.userName) > 0 ){

            pos = pos->next;
            count++;

        }else{

            pos->next = pos;
            pos->data = item;

        }
    }

    return true;
}

tList deleteAtPosition(tPosL pos,tList *list) {

    if (isEmptyList(*list)) return *list;// Lista vacía, no se puede eliminar

    if (findItem(pos->data.userName, *list) == LNULL) {
        return *list; // Posición inválida
    }else if (pos == *list) {
        *list = pos->next;
        return *list;
    } else if (pos->next == LNULL) {
        previous(pos, *list)->next = LNULL;
        free(pos);
        return *list;
    }else{
        tPosL q;
        q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        return *list;
    }
}