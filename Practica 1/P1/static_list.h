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


tList createEmptyList();
bool isEmptyList(tList list);
tPosL first(tList list);
tPosL last(tList list);
tPosL next(tPosL p, tList list);
tPosL previous(tPosL p, tList list);
bool insertItem(tItemL item, tPosL p, tList *list);
void deleteAtPosition(tPosL p, tList *list);
tItemL getItem(tPosL p, tList list);
void updateItem(tItemL item, tPosL p, tList *list);
tPosL findItem(tUserName username, tList list);

#endif