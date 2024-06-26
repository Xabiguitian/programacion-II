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

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list) {
    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1,
                   (strcmp(param2, "") == 0) ? "" : (strcmp(param2, "basic") == 0) ? "basic" : "pro");

            tItemL newUser;
            strcpy(newUser.userName, param1);
            newUser.userCategory = (strcmp(param2, "basic") == 0) ? basic : pro;
            newUser.numPlay = 0;


            if (findItem(newUser.userName, *list) == LNULL) {
                if (insertItem(newUser, list->numUsers, list)) {
                    printf("* New: user %s category %s\n", newUser.userName,
                           (newUser.userCategory == basic) ? "basic" : "pro");
                } else {
                    printf("+ Error: New not possible\n");
                }
            }else {
                printf("+ Error: New not possible\n");
            }
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            if (isEmptyList(*list) == 0) {
                tPosL pos = findItem(param1, *list);
                if (pos != LNULL) {
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
            break;
        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);

            if (isEmptyList(*list) == 0) {
                tPosL upgradePos = findItem(param1, *list);
                if (upgradePos != LNULL) {
                    tItemL userToUpgrade = getItem(upgradePos, *list);
                    if (userToUpgrade.userCategory == basic) {
                        userToUpgrade.userCategory = pro;
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
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);

            if (isEmptyList(*list) == 0) {
                tPosL playPos = LNULL;
                playPos = findItem(param1, *list);
                if (playPos != LNULL) {
                    tItemL userToPlay = getItem(playPos, *list);
                    userToPlay.numPlay++;
                    printf("* Play: user %s plays song %s numplays %d\n", userToPlay.userName, param2,
                           userToPlay.numPlay);
                    updateItem(userToPlay, playPos, list);
                } else {
                    printf("+ Error: Play not possible\n");
                }
            } else {
                printf("+ Error: Play not possible\n");
            }
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);

            for (int i = 0; i < list->numUsers; i++) {
                tItemL user = list->userList[i];
                printf("User %s category %s numplays %d\n", user.userName,
                       (user.userCategory == basic) ? "basic" : "pro", user.numPlay);
            }

            printf("Category  Users  Plays  Average\n");
            int basicUsers = 0, proUsers = 0, totalPlays_pro = 0, totalPlays_basic=0;
            for (int i = 0; i < list->numUsers; i++) {
                tItemL user = list->userList[i];
                if (user.userCategory == basic) {
                    basicUsers++;
                    totalPlays_basic += user.numPlay;
                } else {
                    proUsers++;
                    totalPlays_pro += user.numPlay;
                }
            }
            float avgBasic = (basicUsers > 0) ? (float)totalPlays_basic / (float)basicUsers : 0;
            float avgPro = (proUsers > 0) ? (float)totalPlays_pro / (float)proUsers : 0;
            printf("Basic     %5d %6d %8.2f\n", basicUsers, totalPlays_basic, avgBasic);
            printf("Pro       %5d %6d %8.2f\n", proUsers, totalPlays_pro, avgPro);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        tList list;
        createEmptyList(&list);

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    char *file_name = "new.txt";

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




