/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#ifndef USER_LIST_H
#define USER_LIST_H

#include "types.h"
#include "song_list.h"

typedef int tPosU; // Posición en la lista de usuarios

typedef struct tItemU { //Estructura para un elemento de la lista de usuarios, en el que se especifica el nombre de usuario, el numero de reproducciones y la categoria del mismo
    tUserName userName;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tListS songList;
} tItemU;

typedef struct tListU { // estructura para la lista de usuarios
    tItemU userList[MAX_USERS]; // Array de elementos de usuario
    int numUsers; // Numero actual de usuarios en la lista
} tListU;

void createEmptyListU(tListU *list); //Crea una lista inicializada con el número de usuarios en 0
bool isEmptyListU(struct tListU list); //Comprueba que la lista esté vacia
tItemU getItemU(tPosU pos,struct tListU list); //Busca el usuario en la posición indicada
void updateItemU(tItemU item, tPosU pos,struct tListU *list); //Reemplaza el elemento en la posición indicada
tPosU firstU(struct tListU list); //Si la lista contiene elementos devuelve el de la primera posición,si está vacia devuelve NULLU
tPosU lastU(struct tListU list); //Si la lista contiene elementos devuelve el de la última posición,si está vacia devuelve NULLU
tPosU nextU(tPosU pos,tListU list); //Si existe siguiente posición devuelve el elemento de dicha, si es la última o inválida devuelve NULLU
tPosU previousU(tPosU pos,tListU list);//Si existe anterior posición devuelve el elemento de dicha, si es la primera o inválida devuelve NULLU

tPosU findItemU(tUserName username, tListU list); //Busca un usuario, si lo encuentra devuelve la posición, si no devuelve LNULLU
bool insertItemU (tItemU item, tListU *list); //Si la lista está llena devuelve false, si la lista está vacia inserta el item en la primera posición y si no está vacia ni llena busca un lugar para insertarlo en la posición correcta
void deleteAtPositionU (tPosU pos, tListU *list); //Si la posición está en la lista y no tiene canciones, elimina el usuario y en caso de no ser el último, recoloca la lista

#endif
