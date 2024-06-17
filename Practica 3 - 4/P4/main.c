/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 08 / 03 / 24
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "song_list.h"
#include "user_list.h"

#define MAX_BUFFER 255

/*
 *  Objetivo: Agregar un nuevo usuario a la lista de usuarios.
 *  Precondiciones: list ya existe, param1 es el nombre único del ususario.
 * Postcondiciones:Se agrega un nuevo usuario a la lista de usuarios si no existeç
 * se manda un mensaje indicando si fue un éxito.
 * Entradas: tListU list es la lista de usuarios, param1 es el nombre único del ususario,
 * y param 2 es la categoría.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void New(char *param1, char *param2, tListU *list) {
    tItemU newUser;
    strcpy(newUser.userName, param1);
    newUser.userCategory = (strcmp(param2, "basic") == 0) ? basic : pro;
    newUser.totalPlayTime = 0;
    createEmptyListS(&newUser.songList);

    if (findItemU(newUser.userName, *list) == NULLU) {
        if (insertItemU(newUser, list)) {
            printf("* New: user %s category %s\n", newUser.userName,
                   (newUser.userCategory == basic) ? "basic" : "pro");
        } else {
            printf("+ Error: New not possible\n");
        }
    } else {
        printf("+ Error: New not possible\n");
    }
}



/*
 *  Objetivo: Eliminar un usuario a la lista de usuarios.
 *  Precondiciones: list ya existe, param1 es el nombre único del ususario.
 * Postcondiciones:Se elimina un usuario a la lista de usuarios si existe
 * se manda un mensaje indicando si fue un éxito.
 * Entradas: tListU list es la lista de usuarios, param1 es el nombre único del ususario.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void Delete(char *param1, tListU *list) {
    if (!isEmptyListU(*list)) {
        tPosU pos = findItemU(param1, *list);
        if (pos != NULLU) {
            tItemU deletedUser = getItemU(pos, *list);
            deleteAtPositionU(pos, list);
            printf("* Delete: user %s category %s totalplaytime %d\n", deletedUser.userName,
                   (deletedUser.userCategory == basic) ? "basic" : "pro", deletedUser.totalPlayTime);
        } else {
            printf("+ Error: Delete not possible\n");
        }
    } else {
        printf("+ Error: Delete not possible\n");
    }
}



/*
 *  Objetivo: Aumentar la categoría de un usuario basic.
 *  Precondiciones: list ya existe, param1 es el nombre único del ususario.
 * Postcondiciones:Se actualiza al usuario a una categoría superior y
 * se manda un mensaje indicando si fue un éxito.
 * Entradas: tListU list es la lista de usuarios, param1 es el nombre único del ususario.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void Upgrade(char *param1, tListU *list) {
    if (!isEmptyListU(*list)) {
        tPosU upgradePos = findItemU(param1, *list);
        if (upgradePos != NULLU) {
            tItemU userToUpgrade = getItemU(upgradePos, *list);
            if (userToUpgrade.userCategory == basic) {
                userToUpgrade.userCategory = pro;
                printf("* Upgrade: user %s category pro\n", userToUpgrade.userName);
                updateItemU(userToUpgrade, upgradePos, list);
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
 *  Objetivo: Reproduce una canción durante ciertos minutos a un usuario.
 *  Precondiciones: list ya existe, param1 es el nombre único del ususario,
 *  param2 es el título de la canción y param3 los minutos.
 * Postcondiciones:Se registra el tiempo de reproducción, y si el usuario y
 * de la canción existen.
 * Entradas: tListU list es la lista de usuarios, param1 es el nombre único del ususario,
*  param2 es el título de la canción y param3 los minutos.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void Play(char *param1, char *param2, char *param3, tListU *list) {
    int minutos;
    sscanf(param3, "%d",&minutos);
    if (!isEmptyListU(*list)) {
        tPosU posU = findItemU(param1, *list);
        if(posU == NULLU){
            printf("+ Error: Play not possible\n");
            return;
        }
        tPosS song = findItemS(param2, posU->data.songList);
        if (posU != NULLU && song != NULLS) {
            tItemU userToPlay = getItemU(posU, *list);
            userToPlay.totalPlayTime = userToPlay.totalPlayTime + minutos;
            printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n", userToPlay.userName, param2,
                   minutos ,userToPlay.totalPlayTime);
            updateItemU(userToPlay, posU, list);
            tItemS songToPlay = getItemS(song, (*list)->data.songList);
            tListS listS = (*list)->data.songList;
            songToPlay.playTime = songToPlay.playTime + minutos;
            updateItemS(songToPlay, song, &listS);
            (*list)->data.songList = listS;
        } else {
            printf("+ Error: Play not possible\n");
        }
    } else {
        printf("+ Error: Play not possible\n");
    }
}





/*
 *  Objetivo: Elimina un ususario cuyo tiempo total excede el límite.
 *  Precondiciones: list ya existe, param1 es el nombre único del ususario.
 * Postcondiciones:Se elimina el usuario cuyo tiempo de reproduccion exceda el límite y
 * se muestra un mensaje que indica éxito o fracaso.
 * Entradas: tListU list es la lista de usuarios, maxTime el tiempo máximo de reproducción,
 * y param1 el nombre de ususario.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void Remove(char *param1, tListU *list) { // Elimina usuarios "basic" que exceden el límite de reproducción
    int maxTime;
    sscanf(param1, "%d", &maxTime); // Añade el número indicado en param1 en maxTime
    int numbasic = 0; // Inicializa el contador numbasic a 0

    if (maxTime < 0){
        printf("+ Error: Remove not possible\n");
        return;
    }

    tPosU pos = firstU(*list);
    tPosU prev = NULLU;

    while (pos != NULLU) {
        if (pos->data.userCategory == basic && pos->data.totalPlayTime > maxTime) { // Basic supera el tiempo de reproducción
            printf("Removing user %s totalplaytime %d\n", pos->data.userName, pos->data.totalPlayTime);
            // Muestra por pantalla que se está llevando a cabo la eliminación del usuario

            // Elimina las canciones del usuario
            tPosS songPos = firstS(pos->data.songList);
            while (songPos != NULLS) {
                tPosS songToDelete = songPos;
                songPos = songPos->next;
                deleteAtPositionS(songToDelete, &pos->data.songList);
            }

            // Elimina el usuario
            tPosU userToDelete = pos;
            if (prev == NULLU) {
                // Si estamos eliminando el primer nodo
                *list = pos->next;
            } else {
                prev->next = pos->next;
            }
            pos = pos->next;
            free(userToDelete);

            numbasic++; // Suma 1 a nuestro contador de usuarios basic para después hacer la comprobación de si hay que mostrar por pantalla un error
        } else {
            prev = pos;
            pos = pos->next;
        }
    }

    if (numbasic == 0 || isEmptyListU(*list)) { // Comprueba si no hay ningún usuario basic o si la lista de usuarios está vacía
        printf("+ Error: Remove not possible\n"); // Muestra un error si lo anterior ocurre
    }
}



/*
 *  Objetivo: Mostrar las estadísticas sobre los usuarios y las canciones.
 *  Precondiciones: tListU list ya existe.
 * Postcondiciones: Se muestran estadísticas sobre los usuarios y sus canciones, incluyendo
 * el número total de usuarios, el tiempo total de reproducción, y el tiempo
 * promedio de reproducción por usuario y categoría
 * Entradas: tListU es la lista de usuarios.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir y las estadisticas.
 */
void Stats(tListU *list) {
    if (!isEmptyListU(*list)) {
        int basicUsers = 0, proUsers = 0, totalPlaysPro = 0, totalPlaysBasic = 0;
        for (tPosU posU = *list; posU != NULLU; posU = posU->next) {
            printf("User %s category %s totalplaytime %d\n", posU->data.userName,
                   (posU->data.userCategory == basic) ? "basic" : "pro", posU->data.totalPlayTime);
            tPosS posS = posU->data.songList;
            if (isEmptyListS(posS)) {
                printf("No songs\n");
            }
            for (posS = posU->data.songList; posS != NULLU; posS = posS->next) {
                printf("Song %s playtime %d\n", posS->data.songTitle, posS->data.playTime);
            }
            printf("\n");

            if (posU->data.userCategory == basic) {
                basicUsers++;
                totalPlaysBasic += posU->data.totalPlayTime;
            } else {
                proUsers++;
                totalPlaysPro += posU->data.totalPlayTime;
            }
        }

        printf("Category  Users  TimePlay  Average\n");
        float avgBasic = (basicUsers > 0) ? (float) totalPlaysBasic / basicUsers : 0;
        float avgPro = (proUsers > 0) ? (float) totalPlaysPro / proUsers : 0;
        printf("Basic     %5d %9d %8.2f\n", basicUsers, totalPlaysBasic, avgBasic);
        printf("Pro       %5d %9d %8.2f\n", proUsers, totalPlaysPro, avgPro);
    } else {
        printf("+ Error: Stats not possible\n");
    }
}


/*
 *  Objetivo: Agregar una nueva canción a la lista de canciones de un usuario.
 *  Precondiciones: tListU list ya existe, param1 es el nombre de usuario y param2 es la canción.
 * Postcondiciones: Se agrega la canción a la lista de canciones del usuario si el usuario
 * existe y la canción no está ya en su lista, y se muestra si fue un exito  o no.
 * Entradas: tListU es la lista de usuarios param1 el nombre de usuario, y param2 la canción.
 * Salidas:Mensaje que indica si la operación se pudo o no cumplir.
 */
void Add (char *param1, char *param2, tListU *list){ //Función que añade una canción a un usuario
    if(!isEmptyListU(*list)) {
        tPosU posU = findItemU(param1, *list); //Busca y guarda la posición del usuario que se busca
        tPosS posS = findItemS(param2, posU->data.songList); //Busca y guarda la posición de la canción que se busca

        if (posU != NULLU && isEmptyListU(*list) == 0 && posS ==
                                                         NULLS) { //Comprueba si la canción ya existe en dicho usuario, si la lista de usuarios está vacía o si el usuario existe
            tItemS newSong; //Crea una nueva canción
            strcpy(newSong.songTitle, param2); //Le añade si título
            newSong.playTime = 0; //Inicializa el tiempo de reproducción en 0
            tListS listS = posU->data.songList; //Hace una copia de la lista de canciones para poder hacer comprobaciones más facilmente más adelante

            if (insertItemS(newSong, &listS) == true) { //Añade una canción y comprueba si se pudo hacer
                posU->data.songList = listS;
                printf("* Add: user %s adds song %s\n", posU->data.userName,
                       param2); //Muestra que se añadió correctamente la canción

            } else {
                printf("+ Error: Add not possible\n"); //Si lo anterior no se cumple muestra un error
            }
        } else {
            printf("+ Error: Add not possible\n"); //Si lo anterior no se cumple muestra un error
        }
    } else {
        printf("+ Error: Add not possible\n"); //Si lo anterior no se cumple muestra un error
    }
}




/*
 *  Objetivo: Bajar a 0 el playtime de los usuarios basic con diferencia menor de 30 minutos con el máximo basic.
 *  Precondiciones: tListU list ya existe y maxTimeBasic es el tiempo del basic con más minutos.
 * Postcondiciones: Se le baja a 0  los minutos reprodocidos a los usuarios basic con diferencia menor de 30 minutos con el máximo basic.
 * Entradas: tListU es la lista de usuarios.
 * Salidas:Mensaje que indica la cantidad de ususarios con el tiempo reestablecido.
 */
void applyPromo(tListU *list){
    if(!isEmptyListU(*list)) {
        int maxTimeBasic = 0;
        for (tListU copyList1 = *list; copyList1->next != NULLU; copyList1 = copyList1->next) {
            if (copyList1->data.userCategory == basic && copyList1->data.totalPlayTime > maxTimeBasic) {
                maxTimeBasic = copyList1->data.totalPlayTime;
            }
        }
        int contApplyPromo = 0;
        for (tListU copyList2 = *list; copyList2 != NULLU; copyList2 = copyList2->next) {
            if (copyList2->data.userCategory == basic && copyList2->data.totalPlayTime >= maxTimeBasic - 30) {
                int contSongs = 0;
                for (tListS copyListS = copyList2->data.songList; copyListS != NULLS; copyListS = copyListS->next) {
                    if (copyListS->data.playTime > 0) {
                        contSongs++;
                    }
                }
                if (contSongs > 3) {
                    printf("* ApplyPromo: user %s\n", copyList2->data.userName);
                    tPosU item = findItemU(copyList2->data.userName, *list);
                    item->data.totalPlayTime = 0;
                    updateItemU(item->data, copyList2, list);
                    contApplyPromo++;
                }
            }
        }
        if(contApplyPromo > 0){
            printf("* Promo applied to %d users\n", contApplyPromo);
        }else {
            printf("+ Error: ApplyPromo not possible\n");
        }
    }else{
        printf("+ Error: ApplyPromo not possible\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListU *list) {
    switch (command) {
        case 'N':

            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1,
                   (strcmp(param2, "") == 0) ? "" : (strcmp(param2, "basic") == 0) ? "basic" : "pro");
            New(param1, param2, list);
            break;

        case 'D':

            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            Delete(param1, list);
            break;

        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            Upgrade(param1, list);
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s minutes %s\n", commandNumber, command, param1, param2, param3);

            Play(param1, param2, param3, list);
            break;

        case 'A':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2); //Indica que empieza una nueva acción, en la que especifica su número, la letra que la representa, el usuario y la canción

            Add (param1, param2, list); //Ejecuta Add
            break;

        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);

            Stats(list);
            break;

        case 'R':
            printf("********************\n");
            printf("%s %c: maxtime %s\n", commandNumber, command, param1); //Indica que empieza una nueva acción, en la que especifica su número y la letra que la representa

            Remove(param1, list); //Esjecuta Remove
            break;

        case 'M':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command); //Indica que empieza una nueva acción, en la que especifica su número y la letra que la representa

            applyPromo(list); //Esjecuta Remove
            break;

        default:
            break;
    }
}

void readTasks(char *filename, tListU *list) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {


        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    tListU list;
    createEmptyListU(&list);

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