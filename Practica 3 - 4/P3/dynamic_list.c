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

void createEmptyList(tList *list) {
    *list = LNULL;
}

bool isEmptyList(tList list) {
    return list == LNULL;
}

bool createNode(tPosL *pos) {
    *pos = malloc(sizeof(struct tNode));
    return *pos != LNULL;
}

int numUsers(tList list) {
    int count = 0;
    for (tPosL pos = list; pos != LNULL; pos = pos->next) {
        count++;
    }
    return count;
}

tPosL findItem(tUserName username, tList list) {
    for (tPosL pos = list; pos != LNULL; pos = pos->next) {
        if (strcmp(pos->data.userName, username) == 0) {
            return pos;
        }
    }
    return LNULL;
}

tItemL getItem(tPosL pos, tList list) {
    return pos->data;
}

void updateItem(tItemL item, tPosL pos, tList *list) {
    pos->data = item;
}

tPosL first(tList list) {
    return list;
}

tPosL last(tList list) {
    if (isEmptyList(list)) {
        return LNULL;
    }
    tPosL pos;
    for (pos = list; pos->next != LNULL; pos = pos->next);
    return pos;
}

tPosL next(tPosL pos, tList list) {
    return pos->next;
}

tPosL previous(tPosL pos, tList list) {
    if (pos == list) {
        return LNULL;
    }
    tPosL posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}

bool insertItem(tItemL item, tPosL pos, tList *list) {
    tPosL posInsert;
    if (!createNode(&posInsert)) {
        return false;
    }

    posInsert->data = item;
    posInsert->next = LNULL;

    if (*list == LNULL) {
        *list = posInsert;
        return true;
    }

    if (findItem(item.userName, *list) != LNULL) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    if (pos == LNULL) {
        tPosL prev = LNULL;
        tPosL current = *list;
        while (current != LNULL && strcmp(item.userName, current->data.userName) > 0) {
            prev = current;
            current = current->next;
        }
        if (prev == LNULL) {
            posInsert->next = *list;
            *list = posInsert;
        } else {
            posInsert->next = current;
            prev->next = posInsert;
        }
    } else if (pos == *list) {
        posInsert->next = pos;
        *list = posInsert;
    } else {
        posInsert->next = pos->next;
        pos->next = posInsert;
    }

    return true;
}

void deleteAtPosition(tPosL pos, tList *list) {
    if (isEmptyList(*list)) return;

    if (findItem(pos->data.userName, *list) == LNULL) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == LNULL) {
        tPosL prev = previous(pos, *list);
        prev->next = LNULL;
        free(pos);
    } else {
        tPosL q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}