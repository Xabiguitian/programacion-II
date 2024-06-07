/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"

#define LNULL NULL

typedef struct tNode *tPosL;

typedef struct tNode{
    tItemL data;
    tPosL next;
} tNode;

typedef tPosL tList;

tList createEmptyList(tList *list);
bool isEmptyList(tList list);
bool createNode(tPosL *pos);
bool insertItem(tItemL item, tList *list);
tList deleteAtPosition(tPosL pos, tList *list);
tItemL getItem(tPosL pos, tList list);
tList updateItem(tItemL item, tPosL pos, tList *list);
tPosL findItem(tUserName username, tList list);
tPosL first(tList list);
tPosL last(tList list);
tPosL next(tPosL pos, tList list);
tPosL previous(tPosL pos, tList list);

#endif
