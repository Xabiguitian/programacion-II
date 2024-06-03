#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LNULL -1

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