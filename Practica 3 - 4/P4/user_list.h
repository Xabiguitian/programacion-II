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
#include "song_list.h"

#define NULLU NULL


typedef struct tItemU { //Estructura para un elemento de la lista de usuarios, en el que se especifica el nombre de usuario, el numero de reproducciones y la categoria del mismo
    tUserName userName;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tListS songList;
} tItemU;

typedef struct tNode *tPosU;

typedef struct tNode{
    tItemU data;
    tPosU next;
} tNode;

typedef tPosU tListU;

void createEmptyList(tListU *list);
bool isEmptyList(tListU list);
bool createNode(tPosU *pos);
int numUsers(tListU list);
bool insertItem(tItemU item, tListU *list);
void deleteAtPosition(tPosU pos, tListU *list);
tItemU getItem(tPosU pos, tListU list);
void updateItem(tItemU item, tPosU pos, tListU *list);
tPosU findItem(tUserName username, tListU list);
tPosU first(tListU list);
tPosU last(tListU list);
tPosU next(tPosU pos, tListU list);
tPosU previous(tPosU pos, tListU list);

#endif