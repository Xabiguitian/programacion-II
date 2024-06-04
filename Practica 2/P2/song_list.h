/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#define MAX_LIST_LENGTH 25

#ifndef SONG_LIST_H
#define SONG_LIST_H

#include "types.h"
//#include "user_list.h"

typedef int tPosS; // Define un elemento que contiene ls posición en la lista de canciones

typedef tSong tItemS; // Define cada tItemS como un elemento tSong

typedef struct tListS { // Define una estructura para la lista de usuarios
    tItemS songList[MAX_LIST_LENGTH];
    tPosS numSongs;
} tListS;



void createEmptyListS (tListS *list); //Crea una lista vacia
bool isEmptyListS (tListS list); //Verifica que la lista está vacia
tPosS firstS (tListS list); //Devuelve la primera posición
tPosS lastS (tListS list); //Devuelve la última posición
tPosS nextS (tPosS pos,tListS list); //Devuelve la siguiente posición
tPosS previousS (tPosS pos,tListS list); //Devuelve la anterior posición
bool insertItemS (tItemS item, tPosS pos, tListS *list); //Si la lista no está llena incrementa el número y añade el elemento en la posición indicada
void deleteAtPositionS(tPosS pos,tListS *list); //Si la lista tiene elementos y la posición es correcta, elimina dicho elemento y recoloca el resto decrementando el número de usuarios
tItemS getItemS (tPosS pos,tListS list); //Devuelve el elemento que hay en la posición que se indique
void updateItemS (tItemS item, tPosS pos, tListS *list); //Cambia el elemento de la lista en la posición indicada por el item seleccionado
tPosS findItemS (tSongTitle songtitle, tListS list); //Se busca un usuario, si lo encuentra devuelve la posición, si no devuelve NULLS

#endif
