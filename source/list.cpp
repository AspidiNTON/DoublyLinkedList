#include "list.h"

const int LIST_MAX_SIZE = 10;

struct List {
    ListElem elements[LIST_MAX_SIZE];
    int rightPointers[LIST_MAX_SIZE];
    int leftPointers[LIST_MAX_SIZE];
    int head;
    int tail;
    int freeElement;
};

void initList(List** list){
    *list = (List*)calloc(1, sizeof(List));
    (*list)->head = 0;
    (*list)->tail = 0;
    (*list)->freeElement = 1;
    for (int i = 1; i < LIST_MAX_SIZE - 1; ++i) {
        (*list)->elements[i] = - i - 1;
    }
    (*list)->elements[LIST_MAX_SIZE - 1] = 0;
}

bool pushBack(List* list, ListElem elem){
    if (list->freeElement == 0) {
        printf("Unable to push: list is full\n");
        return false;
    }
    int nextFreeElement = -list->elements[list->freeElement];
    if (list->head == 0) {
        list->elements[list->freeElement] = elem;
        list->rightPointers[list->freeElement] = 0;
        list->leftPointers[list->freeElement] = 0;
        list->head = list->freeElement;
        list->tail = list->freeElement;
        list->freeElement = nextFreeElement;
    } else {
        list->elements[list->freeElement] = elem;
        list->leftPointers[list->freeElement] = list->tail;
        list->rightPointers[list->freeElement] = 0;
        list->rightPointers[list->tail] = list->freeElement;
        list->tail = list->freeElement;
        list->freeElement = nextFreeElement;
    }
    return true;
}

void printList(List* list){
    int id = list->head;
    while (id != 0) {
        printElement(list->elements[id]);
        putchar(' ');
        id = list->rightPointers[id];
    }
    putchar('\n');
}