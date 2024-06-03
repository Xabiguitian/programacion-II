/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Xabier Guitián López LOGIN 1: x.guitian@udc.es
 * AUTHOR 2: Lucas Marqués Núñez LOGIN 2: lucas.marques@udc.es
 * GROUP: 2.4
 * DATE: 16 / 02 / 24
 */

#include "static_list.h"
#include <stdio.h>
#include <stdbool.h>
#define tamanolista 25

void createEmptyList(char tList[]) {
    for(int i = 0; i < tamanolista; i++) {
        tList[i] = '\0';
    }
}


bool isEmptyList(char tList[], int size) {
    for(int i = 0; i < size; i++) {
        if(tList[i] != '\0') {
            return false;
        }
    }
    return true;
}

int first (char tList[]) {
    for(int i = 0; i < tamanolista; i++) {
        if(tList[i] != '\0'){
            return i;
        }
    }
    return -1;
}

int last (char tList[]) {
    for(int i = 0; i < tamanolista; i++) {
        if(tList[i] == '\0'){
            return i-1;
        }
    }
    return -1;
}

void next (int tPosL, char tList[]) {
    if (tList[tPosL+1]!= '\0') {
        printf("\n%d", tList[tPosL+1]);
    }else {
        printf("\nLNULL");
    }
}

void previous (int tPosL, char tList[]) {
    if (tPosL > 0 && tList[tPosL-1]!= '\0') {
        printf("\n%d", tList[tPosL-1]);
    }else {
        printf("\nLNULL");
    }
}

bool insertItem (tItemL L, int tPosL, tItemL tList[]) {
    if(tPosL<0 || tPosL>tamanolista){
        return false;
    }
    if (tPosL == '\0'){
        tList[tamanolista] = L;
        return true;

    }else{
        tList[tPosL-1] = L;
        return true;
    }

}
