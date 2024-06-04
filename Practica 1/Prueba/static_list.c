#include "static_list.h"
#include <string.h>

tList createEmptyList() {
    tList list;
    list.size = 0;
    return list;
}

int isEmptyList(tList list) {
    return list.size == 0;
}

int first(tList list) {
    return 0;
}

int last(tList list) {
    return list.size - 1;
}

int next(int position, tList list) {
    return (position < list.size - 1) ? position + 1 : -1;
}

int previous(int position, tList list) {
    return (position > 0) ? position - 1 : -1;
}

int insertItem(tItemL item, int position, tList *list) {
    if (list->size >= MAX_LIST_SIZE)
        return 0;

    if (position < 0 || position > list->size)
        return 0;

    for (int i = list->size; i > position; i--) {
        list->items[i] = list->items[i - 1];
    }

    list->items[position] = item;
    list->size++;
    return 1;
}

void deleteAtPosition(int position, tList *list) {
    if (position < 0 || position >= list->size)
        return;

    for (int i = position; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }

    list->size--;
}

tItemL getItem(int position, tList list) {
    return list.items[position];
}

void updateItem(tItemL item, int position, tList *list) {
    if (position < 0 || position >= list->size)
        return;

    list->items[position] = item;
}

int findItem(tUserName userName, tList list) {
    for (int i = 0; i < list.size; i++) {
        if (strcmp(list.items[i].userName, userName) == 0)
            return i;
    }
    return -1;
}