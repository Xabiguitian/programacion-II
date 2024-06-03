/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */
#include "types.h"
#include <string.h>
#include <stdbool.h>
#define LNULL (-1)

void createEmptyList (tList *list) {
    list->numUsers = 0;

}

bool isEmptyList (tList *list){
    return list->numUsers == 0;
}

tPosL first (tList *list){
    if (isEmptyList(list) == 1){
        return LNULL;
    }
        return 0;
}

tPosL last (tList *list){
    if (isEmptyList(list) == 1){
        return LNULL;
    }
        return (list->numUsers -1);
}

tPosL next(tPosL pos,tList *list){
    if (pos > list->numUsers || pos > 0){
        return LNULL;
    }
    return pos+1;
}

tPosL previous(tPosL pos,tList *list){
    if (pos > list->numUsers || pos > 0){
        return LNULL;
    }
    return pos-1;
}

bool insertItem (tItemL item, tPosL pos, tList *list) {
    if (list->numUsers >= MAX_USERS){
        return false;
    }

    if (pos < 0 || pos > list->numUsers){
        return false;
    }

    if (pos > list->numUsers){
        list->userList[list->numUsers] = item;
        return true;
    }

    for (int i = list->numUsers+1; i >= pos; i--) {
        list->userList[i] = list->userList[i-1];
    }

    list->userList[pos] = item;
    list->numUsers++;
    return true;

}

void deleteAtPosition(tPosL pos, tList *list){
    if (isEmptyList(list)) {
        return;
    }

    if (pos < 0 || pos >= list->numUsers) {
        return;
    }

    for (int i = pos; i < list->numUsers - 1; i++) {
        list->userList[i] = list->userList[i + 1];
    }

    list->numUsers--;
}

tItemL getItem (tPosL pos, tList list){
    return list.userList[pos];
}

void updateItem (tItemL item, tPosL pos, tList *list){
    list->userList[pos] = item;
}

tPosL findItem(tUserName username,tList list){
    for (int i = 0; i < list.numUsers; i++) {
        if (strcmp(list.userList[i].userName, username) == 0) {
            return i;
        }
    }
    return LNULL;
}