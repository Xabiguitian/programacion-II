/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include "user_list.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void createEmptyList(tListU *list) {
    *list = NULLU;
}

bool isEmptyList(tListU list) {
    return list == NULLU;
}

bool createNode(tPosU *pos) {
    *pos = malloc(sizeof(struct tNode));
    return *pos != NULLU;
}

int numUsers(tListU list) {
    int count = 0;
    for (tPosU pos = list; pos != NULLU; pos = pos->next) {
        count++;
    }
    return count;
}

tPosU findItem(tUserName username, tListU list) {
    for (tPosU pos = list; pos != NULLU; pos = pos->next) {
        if (strcmp(pos->data.userName, username) == 0) {
            return pos;
        }
    }
    return NULLU;
}

tItemU getItem(tPosU pos, tListU list) {
    return pos->data;
}

void updateItem(tItemU item, tPosU pos, tListU *list) {
    pos->data = item;
}

tPosU first(tListU list) {
    return list;
}

tPosU last(tListU list) {
    if (isEmptyList(list)) {
        return NULLU;
    }
    tPosU pos;
    for (pos = list; pos->next != NULLU; pos = pos->next);
    return pos;
}

tPosU next(tPosU pos, tListU list) {
    return pos->next;
}

tPosU previous(tPosU pos, tListU list) {
    if (pos == list) {
        return NULLU;
    }
    tPosU posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}

bool insertItem(tItemU item, tListU *list) {
    tPosU posInsert;
    if (!createNode(&posInsert)) {
        return false;
    }

    posInsert->data = item;
    posInsert->next = NULLU;

    if (*list == NULLU) {
        *list = posInsert;
        return true;
    }

    if (findItem(item.userName, *list) != NULLU) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    tPosU prev = NULLU;
    tPosU current = *list;
    while (current != NULLU && strcmp(item.userName, current->data.userName) > 0) {
        prev = current;
        current = current->next;
    }
    if (prev == NULLU) {
        posInsert->next = *list;
        *list = posInsert;
    } else {
        posInsert->next = current;
        prev->next = posInsert;
    }

    return true;
}

void deleteAtPosition(tPosU pos, tListU *list) {
    if (isEmptyList(*list)) return;

    if (findItem(pos->data.userName, *list) == NULLU) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == NULLU) {
        tPosU prev = previous(pos, *list);
        prev->next = NULLU;
        free(pos);
    } else {
        tPosU q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}