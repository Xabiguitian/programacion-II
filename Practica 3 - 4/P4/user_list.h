/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#ifndef USER_LIST_H
#define USER_LIST_H

#include "types.h"
#include "song_list.h"

#define NULLU NULL


typedef struct tItemU { //Estructura para un elemento de la lista de usuarios, en el que se especifica el nombre de usuario, el numero de reproducciones y la categoria del mismo
    tUserName userName;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tListS songList;
} tItemU;

typedef struct tNodeU *tPosU;

typedef struct tNodeU{
    tItemU data;
    tPosU next;
} tNodeU;

typedef tPosU tListU;

void createEmptyListU(tListU *list);
bool isEmptyListU(tListU list);
bool createNodeU(tPosU *pos);
bool insertItemU(tItemU item, tListU *list);
void deleteAtPositionU(tPosU pos, tListU *list);
tItemU getItemU(tPosU pos, tListU list);
void updateItemU(tItemU item, tPosU pos, tListU *list);
tPosU findItemU(tUserName username, tListU list);
tPosU firstU(tListU list);
tPosU lastU(tListU list);
tPosU nextU(tPosU pos, tListU list);
tPosU previousU(tPosU pos, tListU list);
#endif