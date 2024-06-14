#ifndef PRO2_2023_P1_TYPES_H
#define PRO2_2023_P1_TYPES_H

#define NAME_LENGTH_LIMIT 25 //Longitud máxima de un nombre de usuario y de un título de canción

#define MAX_USERS 25

#include <stdbool.h>

typedef char tUserName[NAME_LENGTH_LIMIT]; //Crea un array para los nombres de usuario
typedef enum {basic, pro} tUserCategory; //Crea las opciones de "basic" y "pro"
typedef int tPlayTime; //Crea un entero para el número de reproducciones
typedef char tSongTitle[NAME_LENGTH_LIMIT]; //Crea un array para los títulos de las canciones

typedef struct Song{ //Estructura para una canción donde se especifica el nombre de la canción y las veces que se ha reproducido
    tSongTitle songTitle;
    tPlayTime playTime;
} tSong;

#endif