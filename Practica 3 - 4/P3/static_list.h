/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <stdbool.h>

#define MAX 25
#define LNULL -1

typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

int numUsers(tList list);
void createEmptyList(tList *list);
bool isEmptyList(tList list);
tPosL first(tList list);
tPosL last(tList list);
tPosL next(tPosL pos, tList list);
tPosL previous(tPosL pos, tList list);
bool insertItem(tItemL item, tList *list);
void deleteAtPosition(tPosL pos, tList *list);
tItemL getItem(tPosL pos, tList list);
void updateItem(tItemL item, tPosL pos, tList *list);
tPosL findItem(tUserName username, tList list);

#endif