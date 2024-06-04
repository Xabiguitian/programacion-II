/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marquess@gmail.com
 * GROUP: 2.4
 * DATE: 22 / 03 / 2024
 */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "user_list.h"
#include "song_list.h"

#define MAX_BUFFER 255


void New(char *param1, char *param2, tListU *list){ //Crea un nuevo usuario
    tItemU newUser; //Crea un nuevo usuario
    strcpy(newUser.userName, param1); //Le pone el nombre indicado al usuario
    newUser.userCategory = (strcmp(param2, "basic") == 0) ? basic : pro; //Le añade su categoría
    newUser.totalPlayTime = 0; //Inicializa el tiempo de reproducción a 0
    newUser.songList.numSongs = 0; //Inicializa el número de canciones a 0
    for (int i = 0; i < MAX_LIST_LENGTH; ++i) {
        strcpy(newUser.songList.songList[i].songTitle, "");
        newUser.songList.songList[i].playTime = 0;
    } //Crea el array de canciones vacio

    if (insertItemU (newUser, list) == true) {
        printf("* New: user %s category %s\n", newUser.userName,
               (newUser.userCategory == basic) ? "basic" : "pro");
    } //Añade el nuevo usuario a nuestra lista de usuarios
    else {
        printf("+ Error: New not possible\n"); //Muestra un error por pantalla si no se cumple el anterior if
    }
}

void Delete (char *param1, tListU *list){ //Función que elimina al usuario
    if (isEmptyListU(*list)==0) { //Comprueba si la lista está vacía
        tPosU pos = findItemU (param1, *list); //Busca la posición del usuario y lo guarda en pos
        if (list->userList[pos].songList.numSongs != 0 && pos != NULLU) { //Comprueba si el numero de canciones es distinto de 0 y si la posición es distinta de nula

            for (int i = firstS(list->userList[pos].songList); i < list->userList[pos].songList.numSongs; ++i) {
                strcpy(list->userList[pos].songList.songList[i].songTitle, "");
                //Elimina los títulos de las canciones
                list->userList[pos].songList.songList[i].playTime = 0;
                //Pone las reproducciones de cada canción a 0
            }
            list->userList[pos].songList.numSongs = 0;
            //Pone el número de canciones a 0

            printf("* Delete: user %s category %s totalplaytime %d\n", list->userList[pos].userName, //Muestra que se eliminó el usuario correctamente
                   (list->userList[pos].userCategory == basic) ? "basic" : "pro", list->userList[pos].totalPlayTime);
            deleteAtPositionU(pos, list); //Elimina el usuario
        }else if(list->userList[pos].songList.numSongs == 0){
            printf("* Delete: user %s category %s totalplaytime %d\n", list->userList[pos].userName, //Muestra que se eliminó el usuario correctamente
                   (list->userList[pos].userCategory == basic) ? "basic" : "pro", list->userList[pos].totalPlayTime);
            deleteAtPositionU(pos, list); //Elimina el usuario
        } else {
            printf("+ Error: Delete not possible\n");
        }
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

void Add (char *param1, char *param2, tListU *list){ //Función que añade una canción a un usuario
    tPosU posU = findItemU(param1, *list); //Busca y guarda la posición del usuario que se busca
    tPosS posS = findItemS(param2, list->userList[posU].songList); //Busca y guarda la posición de la canción que se busca

    if (posU != NULLU && isEmptyListU(*list) == 0 && posS == NULLS){ //Comprueba si la canción ya existe en dicho usuario, si la lista de usuarios está vacía o si el usuario existe
        tItemS newSong; //Crea una nueva canción
        strcpy(newSong.songTitle, param2); //Le añade si título
        newSong.playTime = 0; //Inicializa el tiempo de reproducción en 0
        tListS listS = list->userList[posU].songList; //Hace una copia de la lista de canciones para poder hacer comprobaciones más facilmente más adelante

        if (insertItemS(newSong, nextS(lastS(listS), listS), &list->userList[posU].songList) == true){ //Añade una canción y comprueba si se pudo hacer
            printf("* Add: user %s adds song %s\n", list->userList[posU].userName, param2); //Muestra que se añadió correctamente la canción

        }else {
            printf("+ Error: Add not possible\n"); //Si lo anterior no se cumple muestra un error
        }
    }else{
        printf("+ Error: Add not possible\n"); //Si lo anterior no se cumple muestra un error
    }
}

void Upgrade (char *param1, tListU *list){ //Cambia la categoría del usuario especificado a "pro" solo sí en un principio es "basic"
    tPosU pos = findItemU(param1, *list);
    //Busca y guarda la posición del usuario que se busca

    if (pos != NULLU && isEmptyListU(*list) == 0 && list->userList[pos].userCategory == basic){ //comprueba si la posición no es nula, si la lista no está vacía y si la categoría del usuario es "basic"
        list->userList[pos].userCategory = pro; //Actualiza la categoría del usuario a "pro"
        printf("* Upgrade: user %s category %s\n", list->userList[pos].userName,
               (list->userList[pos].userCategory == basic) ? "basic" : "pro"); // Muestra que se ha upgradeado la categoría del usuario
    }else {
        printf("+ Error: Upgrade not possible\n"); //Si no se cumplen las condiciones del if, muestra un error
    }
}

void Play (char *param1, char *param2, char *param3, tListU *list){ //Función que añade minutos de reproducción a una canción
    tPosU posU = findItemU(param1, *list);
    //Busca y guarda la posición del usuario que se busca

    tPosS posS = findItemS(param2, list->userList[posU].songList);
    //Busca y guarda la posición de la canción que se busca

    if(posU != NULLU && list->numUsers != 0 && posS != NULLS && list->userList[posU].songList.numSongs != 0){ //Comprueba si la posición del usuario no es nula, si la lista de usuarios no está vacía, si la posición de la canción no es nula y si el número de canciones del usuario es distinta de 0
        int minutos; //Crea un parámetro para almacenar enteros
        sscanf(param3, "%d",&minutos); //Añade a minutos, los especificados en la entrada param3
        list->userList[posU].songList.songList[posS].playTime = list->userList[posU].songList.songList[posS].playTime + minutos; //Añade los minutos al tiempo de reproducción de la canción
        list->userList[posU].totalPlayTime = list->userList[posU].totalPlayTime + minutos; //Añade los minutos al tiempo de reproducción total
        printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n", list->userList[posU].userName, param2, minutos, list->userList[posU].totalPlayTime);
        //Muestra que se ha actualizado el número de minutos
    }else {
        printf("+ Error: Play not possible\n"); //Muestra un error si las condiciones del if anterior no se cumplen
    }
}


void Stats (tListU *list){ //Muestra el número de usuarios "basic" y "pro" e imprime las veces escuchadas cada canción
    int countBasic = 0, countPro = 0;
    int numPlayBasic = 0, numPlayPro = 0;
    //Inicializa 4 contadores a 0

    if(isEmptyListU(*list)!=0) { //Comprueba si la lista está vacía
        printf("+ Error: Stats not possible\n"); //Muestra un error si se cumple la anterior condición
    } else {

        for (int i = firstU(*list); i < list->numUsers; i++) { //Bucle que recorre toda la lista de usuarios
            if (list->userList[i].songList.numSongs == 0) { //Comprueba si la lista de canciones está vacía

                printf("User %s category %s totalplaytime %d\nNo songs\n\n", list->userList[i].userName, (list->userList[i].userCategory == basic) ? "basic" : "pro", list->userList[i].totalPlayTime);
                //Muestra el nombre de usuario, la categoría, el tiempo total del reproducción (que debe ser 0) y que no tiene canciones

                (list->userList[i].userCategory == basic) ? countBasic++ : countPro++ ; //Suma uno al respectivo contador según si el usuario es "basic" o "pro"

            } else { //Si la lista no está vacía ejecuta lo siguiente

                printf("User %s category %s totalplaytime %d\n", list->userList[i].userName,
                       (list->userList[i].userCategory == basic) ? "basic" : "pro", list->userList[i].totalPlayTime); //Muestra el nombre de usuario, la categoría y su tiempo total de reproducción
                (list->userList[i].userCategory == basic) ? countBasic++ : countPro++; //Suma uno al respectivo contador según si el usuario es "basic" o "pro"

                (list->userList[i].userCategory == basic) ?(numPlayBasic = numPlayBasic + list->userList[i].totalPlayTime): (numPlayPro = numPlayPro + list->userList[i].totalPlayTime);
                //Suma los minutos de reproducción del usuario al respectivo contador dependiendo de la categoría de procedencia

                for (int j = firstS(list->userList[i].songList); j < list->userList[i].songList.numSongs; ++j) { //Bucle que recorre toda la lista de canciones del usuario
                    printf("Song %s playtime %d\n", list->userList[i].songList.songList[j].songTitle,
                           list->userList[i].songList.songList[j].playTime);//Muestra el título de la canción y el tiempo de reproducción de la misma
                }

                printf("\n"); //Printea un salto de línea para separar al siguiente usuario
            }
        }

        //Se crean dos parámetros para calcular la media
        float averageBasic;
        float averagePro;

        if (countBasic == 0){ //Comprueba si el contador de "basic" está a 0
            averageBasic = 0; //Le da el valor de 0 a averageBasic
        }else { //Si no se cumple la condicón del if
            averageBasic = (float) numPlayBasic / (float) countBasic; //Hace la media de reproducción con respecto al número de usuarios "basic"
        }

        if (countPro == 0){ //Comprueba si el contador de "pro" está a 0
            averagePro = 0; //Le da el valor de 0 a averagePro
        }else { //Si no se cumple la condicón del if
            averagePro = (float) numPlayPro / (float) countPro; //Hace la media de reproducción con respecto al número de usuarios "pro"
        }

        //Muestra el recuento final
        printf("Category  Users  TimePlay  Average\n");
        printf("Basic     %5d %9d %8.2f\n", countBasic, numPlayBasic, averageBasic);
        printf("Pro       %5d %9d %8.2f\n", countPro, numPlayPro, averagePro);

    }

}

void Remove (char *param1, tListU *list){ //Elimina usuarios "basic" que exceden el límite de reproducción
    int maxTime;
    sscanf(param1, "%d",&maxTime); //Añade el número indicado en param1 en maxTime
    int numbasic =0; //Inicializa el contador numbasic a 0

    for (int i = firstU(*list); i <= list->numUsers; ++i) {
        if (list->userList[i].userCategory == basic && list->userList[i].totalPlayTime > maxTime){ //Basic supera el tiempo de reproducción
            printf("Removing user %s totalplaytime %d\n", list->userList[i].userName,
                   list->userList[i].totalPlayTime);
            //Muestra por pantalla que se está llevando a cabo la eliminación del usuario

            for (int j = firstS(list->userList[i].songList); j < list->userList[i].songList.numSongs; ++j) {
                strcpy(list->userList[i].songList.songList[j].songTitle, "");
                list->userList[i].songList.songList[j].playTime = 0;
            } //Elimina las canciones del usuario

            list->userList[i].songList.numSongs = 0; //Pone el número de canciones del usuario a 0

            deleteAtPositionU(i, list); //Elimina el usuario

            numbasic++; //Suma 1 a nuestro contador de usuarios basic para despues hacer la comprobación de si hay que mostrar por pantalla un error

            i--;//Restamos 1 a i para que al eliminar un usuario no haya problemas
        }
    }

    if (numbasic == 0 ||  list->numUsers == 0){ //Comrueba si no hay ningún usuario basic o si la lista de usuarios está vacía
        printf("+ Error: Remove not possible\n"); // Muestra un error si lo anterior ocurre
    }
}



void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListU *list) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1,
                   (strcmp(param2, "") == 0) ? "" : (strcmp(param2, "basic") == 0) ? "basic" : "pro"); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa, el usuario y la categoría

            New(param1, param2, list); //Ejecuta el contenido de New

            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa y el usuario

            Delete(param1, list); //Ejecuta Delete

            break;
        case 'A':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa, el usuario y la canción

            Add (param1, param2, list); //Ejecuta Add
            break;

        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa y el usuario

            Upgrade (param1, list); //Ejecuta Upgrade

            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s minutes %s\n", commandNumber, command, param1, param2, param3); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa, el usuario, la canción y los minutos a añadir a la cancion

            Play(param1, param2, param3, list); //Ejecuta Play

            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);

            Stats(list); //Ejecuta Stats

            break;
        case 'R':
            printf("********************\n");
            printf("%s %c: maxtime %s\n", commandNumber, command, param1); //Indica que empieza una nueva acción, en la que especifica su número y la letra que la representa

            Remove(param1, list); //Esjecuta Remove
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        tListU list;
        list.numUsers = 0;

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "upgrade.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}