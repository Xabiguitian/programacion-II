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

void createEmptyList(tList *list);
bool createNode(tPosL *pos);
bool insertItem(tItemL item, tList *list);
void deleteAtPosition(tPosL pos, tList *list);
struct tItemL getItem(tPosL pos, tList list);
void updateItem(tItemL item, tPosL pos, tList *list);
tPosL findItem(tUserName username, tList list);
tPosL first(struct tList list);
tPosL last(struct tList list);
tPosL next(tPosL pos, tList list);
tPosL previous(tPosL pos, tList list);
bool isEmptyList(struct tList list);

#endif
