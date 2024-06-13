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
#include "user_list.h"

#define NULLS NULL

typedef tSong tItemS; // Define cada tItemS como un elemento tSong

typedef struct tNode *tPosS;

typedef struct tNode{
    tItemS data;
    tPosS next;
} tNode;

typedef tPosS tListS;

void createEmptyListS(tListS *list);
bool isEmptyListS(tListS list);
bool createNodeS(tPosS *pos);
int numUsersS(tListS list);
bool insertItemS(tItemS item, tListS *list);
void deleteAtPositionS(tPosS pos, tListS *list);
tItemS getItemS(tPosS pos, tListS list);
void updateItemS(tItemS item, tPosS pos, tListS *list);
tPosS findItemS(tUserName username, tListS list);
tPosS firstS(tListS list);
tPosS lastS(tListS list);
tPosS nextS(tPosS pos, tListS list);
tPosS previousS(tPosS pos, tListS list);

#endif