/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */

#ifndef PRO2_2023_P2_TYPES_H
#define PRO2_2023_P2_TYPES_H

#define NAME_LENGTH_LIMIT 25

#define MAX_USERS 25

#define NULLU (-1)
#define NULLS (-1)

#include <stdbool.h>



typedef char tUserName[NAME_LENGTH_LIMIT]; //Crea un array para los nombres de usuario
typedef enum {basic, pro} tUserCategory; //Crea las opciones de "basic" y "pro"
typedef int tPlayTime; //Crea un entero para el número de reproducciones
typedef char tSongTitle[NAME_LENGTH_LIMIT]; //Crea un array para los títulos de las canciones

typedef struct Song{ //Estructura para una canción donde se especifica el nombre de la canción y las veces que se ha reproducido
    tSongTitle songTitle;
    tPlayTime playTime;
} tSong;


#endif //PRO2_2023_P2_TYPES_H
