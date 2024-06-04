#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#define NAME_LENGTH_LIMIT 50
#define MAX_LIST_SIZE 100

typedef char tUserName[NAME_LENGTH_LIMIT];
typedef char tSongTitle[NAME_LENGTH_LIMIT];
typedef int tNumPlay;

typedef enum {basic, pro} tUserCategory;

typedef struct tItemL {
    tUserName userName;
    tNumPlay numPlay;
    tUserCategory userCategory;
} tItemL;

typedef struct {
    tItemL items[MAX_LIST_SIZE];
    int size;
} tList;

tList createEmptyList();
int isEmptyList(tList list);
int first(tList list);
int last(tList list);
int next(int position, tList list);
int previous(int position, tList list);
int insertItem(tItemL item, int position, tList *list);
void deleteAtPosition(int position, tList *list);
tItemL getItem(int position, tList list);
void updateItem(tItemL item, int position, tList *list);
int findItem(tUserName userName, tList list);

#endif
