/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */
#include "types.h"
#include "song_list.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void createEmptyListS(tListS *list) {
    *list = NULLS;
}

bool isEmptyListS(tListS list) {
    return list == NULLS;
}

bool createNodeS(tPosS *pos) {
    *pos = malloc(sizeof(struct tNodeS));
    return *pos != NULLS;
}

tPosS findItemS(tUserName username, tListS list) {
    for (tPosS pos = list; pos != NULLS; pos = pos->next) {
        if (strcmp(pos->data.songTitle, username) == 0) {
            return pos;
        }
    }
    return NULLS;
}

tItemS getItemS(tPosS pos, tListS list) {
    return pos->data;
}

void updateItemS(tItemS item, tPosS pos, tListS *list) {
    pos->data = item;
}

tPosS firstS(tListS list) {
    return list;
}

tPosS lastS(tListS list) {
    if (isEmptyListS(list)) {
        return NULLS;
    }
    tPosS pos;
    for (pos = list; pos->next != NULLS; pos = pos->next);
    return pos;
}

tPosS nextS(tPosS pos, tListS list) {
    return pos->next;
}

tPosS previousS(tPosS pos, tListS list) {
    if (pos == list) {
        return NULLS;
    }
    tPosS posPrev;
    for (posPrev = list; posPrev->next != pos; posPrev = posPrev->next);
    return posPrev;
}

bool insertItemS(tItemS item, tListS *list) {
    tPosS posInsert;
    if (!createNodeS(&posInsert)) {
        return false;
    }

    if (findItemS(item.songTitle, *list) != NULLS) {
        free(posInsert);  // Liberar el nodo creado si ya existe el item
        return false;
    }

    posInsert->data = item;
    posInsert->next = NULLS;

    if (*list == NULLS) {
        *list = posInsert;
        return true;
    }


    tPosS prev = NULLS;
    tPosS current = *list;
    while (current != NULLS && strcmp(item.songTitle, current->data.songTitle) > 0) {
        prev = current;
        current = current->next;
    }
    if (prev == NULLS) {
        posInsert->next = *list;
        *list = posInsert;
    } else {
        posInsert->next = current;
        prev->next = posInsert;
    }

    return true;
}

void deleteAtPositionS(tPosS pos, tListS *list) {
    if (isEmptyListS(*list)) return;

    if (findItemS(pos->data.songTitle, *list) == NULLS) {
        return;  // Posición inválida
    } else if (pos == *list) {
        *list = pos->next;
        free(pos);
    } else if (pos->next == NULLS) {
        tPosS prev = previousS(pos, *list);
        prev->next = NULLS;
        free(pos);
    } else {
        tPosS q = pos->next;
        pos->data = q->data;
        pos->next = q->next;
        free(q);
    }
}