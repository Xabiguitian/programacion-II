/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


/*
 Objetivo: Incorpora el usuario en el lugar correspondiente, con la categoría indicada y con su número de reproducciones inicializado a 0
 Entrada: Nombre de usuario, su categoría y puntero a lista
 Salida: Lista con el usuario ya añadido
 Postcondición: Se muestra por pantalla que se ha añadido el usuario o un error
 */
void New(char *param1, char *param2, tList *list){

    //Se crea un usuario y se le pone el nombre indicado, su categoría y el número de reproducciones a 0
    tItemL newUser;
    strcpy(newUser.userName, param1);
    newUser.userCategory = (strcmp(param2, "basic") == 0) ? basic : pro;
    newUser.numPlay = 0;


    if (findItem(newUser.userName, *list) == LNULL) { //Si el item no existe aún en la lista se añade o si no muestra error
         if (insertItem(newUser, list) == true) { //Inserta el usuario en la lista y comprueba si lo ha hecho con éxito
             printf("* New: user %s category %s\n", newUser.userName,
             (newUser.userCategory == basic) ? "basic" : "pro");
         } else {
             printf("+ Error: New not possible\n");
         }
    }else {
        printf("+ Error: New not possible\n");
    }
}

/*
 Objetivo: Busca al usuario en la lista, se eliminará de la misma
 Entrada: Nombre de usuario y puntero a lista
 Salida: La lista con el usuario añadido
 Precondición: La lista no puede estar vacía
 Postcondición: Se muestra por pantalla que se ha eliminado el usuario o un error
 */
void Delete (char *param1, tList *list){
    if (isEmptyList(*list) == 0) { //Comprueba si la lista está vacía y sino muestra por pantalla un error
        tPosL pos = findItem(param1, *list); //Busca el usuario con el nombre especificado y lo añade en una nueva variable
        if (pos != LNULL) { //Comprueba si la posición es nula o no, porque así comprueba si existe el usuario
            tItemL deletedUser = getItem(pos, *list);
            deleteAtPosition(pos, list);
            printf("* Delete: user %s category %s numplays %d\n", deletedUser.userName,
                (deletedUser.userCategory == basic) ? "basic" : "pro", deletedUser.numPlay);
        } else {
            printf("+ Error: Delete not possible\n");
        }
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

/*
 Objetivo: Busca al usuario en la lista y se actualiza su categoría a pro
 Entrada: Nombre de usuario y puntero a lista
 Salida: Lista con el upgrade hecho en el respectivo item
 Precondición: La lista no puede estar vacía
 Postcondición: Se muestra por pantalla que se ha mejorado la categoría del usuario o un error
 */
void Upgrade(char *param1, tList *list){
    if (isEmptyList(*list) == 0) { //Comprueba si la lista está vacía y sino muestra por pantalla un error
        tPosL upgradePos = findItem(param1, *list); //Busca el usuario con el nombre especificado y lo añade en una nueva variable
        if (upgradePos != LNULL) { //Comprueba si la posición es nula o no, porque así comprueba si existe el usuario
            tItemL userToUpgrade = getItem(upgradePos, *list);
            if (userToUpgrade.userCategory == basic) { //Comprueba si la categoría del usuario es basic, y si no muestra un error
                userToUpgrade.userCategory = pro; //Mejora la categoría del usuario
                printf("* Upgrade: user %s category pro\n", userToUpgrade.userName);
                updateItem(userToUpgrade, upgradePos, list);
            } else {
                printf("+ Error: Upgrade not possible\n");
            }
        } else {
            printf("+ Error: Upgrade not possible\n");
        }
    } else {
        printf("+ Error: Upgrade not possible\n");
    }
}

/*
 Objetivo: Busca al usuario en la lista y se incrementa su contador de reproducciones en 1
 Entrada: El nombre de usuario, el nombre de la canción y el puntero a lista
 Salida: La lista con el contador de reproducciones aumentado en 1
 Postcondición: Se muestra por pantalla que se ha incrementado el número de reproducciones del usuario o un error
 */
void Play(char *param1, char *param2, tList *list){
    if (isEmptyList(*list) == 0) { //Comprueba si la lista está vacía y sino muestra por pantalla un error
        tPosL playPos = findItem(param1, *list); //Busca el usuario con el nombre especificado y lo añade en una nueva variable
        if (playPos != LNULL) { //Comprueba si la posición es nula o no, porque así comprueba si existe el usuario
            tItemL userToPlay = getItem(playPos, *list);
            userToPlay.numPlay++; //Suma 1 al número de reproducciones
            printf("* Play: user %s plays song %s numplays %d\n", userToPlay.userName, param2,
                    userToPlay.numPlay);
            updateItem(userToPlay, playPos, list); //Actualiza la lista
        } else {
            printf("+ Error: Play not possible\n");
        }
    } else {
        printf("+ Error: Play not possible\n");
    }
}

/*
 Objetivo: Se muestra la lista completa de usuarios actuales
 Entrada:El puntero a lista
 Salida: Muestra por pantalla la lista de usuarios actuales
 */
void Stats (tList *list){
    if (!isEmptyList(*list)) { //Comprueba si la lista está vacía y sino muestra por pantalla un error
        #ifdef DYNAMIC_LIST //Comprueba si está definido DYNAMIC_LIST, en el caso de que así sea, ejecuta lo que está dentro
        int basicUsers = 0, proUsers = 0, totalPlays_pro = 0, totalPlays_basic=0; //Inicializa diferentes contadores a 0
        for (tPosL pos = *list; pos != LNULL; pos = pos->next) { //Mientras que la posición en la lista no sea nula, ejecuta el bucle
             //Muestra por pantalla la información del usuario
             printf("User %s category %s numplays %d\n", pos->data.userName,
                    (pos->data.userCategory == basic) ? "basic" : "pro", pos->data.numPlay);

            //Suma 1 a los respectivos contadores
            if (pos->data.userCategory == basic) {
                basicUsers++;
                totalPlays_basic += pos->data.numPlay;
           } else {
               proUsers++;
               totalPlays_pro += pos->data.numPlay;
           }

        }
        #endif

        #ifdef STATIC_LIST //Comprueba si está definido STATIC_LIST, en el caso de que así sea, ejecuta lo que está dentro
        int basicUsers = 0, proUsers = 0, totalPlays_pro = 0, totalPlays_basic=0; //Inicializa diferentes contadores a 0
        for (int i = 0; i <= list->lastPos; i++) { //Mientras que estemos dentro de la lista, ejecuta el bucle
            //Muestra por pantalla la información del usuario
            printf("User %s category %s numplays %d\n", list->data[i].userName,
                    (list->data[i].userCategory == basic) ? "basic" : "pro", list->data[i].numPlay);

            //Suma 1 a los respectivos contadores
            if (list->data[i].userCategory == basic) {
                basicUsers++;
                totalPlays_basic += list->data[i].numPlay;
            } else {
                proUsers++;
                totalPlays_pro += list->data[i].numPlay;
            }

        }
        #endif

        //Muestra por pantalla las estadísticas totales recogidas con los diferentes contadores
        printf("Category  Users  Plays  Average\n");
        float avgBasic = (basicUsers > 0) ? (float)totalPlays_basic / (float)basicUsers : 0;
        float avgPro = (proUsers > 0) ? (float)totalPlays_pro / (float)proUsers : 0;
        printf("Basic     %5d %6d %8.2f\n", basicUsers, totalPlays_basic, avgBasic);
        printf("Pro       %5d %6d %8.2f\n", proUsers, totalPlays_pro, avgPro);

    } else {
        printf("+ Error: Stats not possible\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list) {
    switch (command) { //Entra en una parte distinta del switch dependiendo del comando
        case 'N':

            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1,
                   (strcmp(param2, "") == 0) ? "" : (strcmp(param2, "basic") == 0) ? "basic" : "pro");
            New(param1, param2, list); //Ejecuta la función New
            break;

        case 'D':

            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            Delete(param1, list); //Ejecuta la función Delete
            break;

        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            Upgrade(param1, list); //Ejecuta la función Upgrade
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);

            Play(param1, param2, list); //Ejecuta la función Play
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);

            Stats(list); //Ejecuta la función Stats
            break;
        default:
            break;
    }
}

void readTasks(char *filename, tList *list) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {


        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    tList list;
    createEmptyList(&list);

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &list);

    return 0;
}