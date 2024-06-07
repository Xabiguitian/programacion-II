#ifndef PRO2_2023_P1_TYPES_H
#define PRO2_2023_P1_TYPES_H

#define NAME_LENGTH_LIMIT 25

#define MAX_USERS 25

#include <stdbool.h>


typedef char tUserName[NAME_LENGTH_LIMIT]; //Nombre de usuario
typedef char tSongTitle[NAME_LENGTH_LIMIT]; //Titulo de la canción
typedef int tNumPlay; //número de reproducciones

typedef enum {basic, pro} tUserCategory; // Categorias de usuario

typedef struct tItemL { //Estructura para un elemento de la lista de usuarios, en el que se especifica el nombre de usuario, el numero de reproducciones y la categoria del mismo
    tUserName userName;
    tNumPlay numPlay;
    tUserCategory userCategory;
} tItemL;

typedef struct tSong { // Estructura para una canción
    tSongTitle songTitle; // Título de la canción
} tSong;


#endif