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
        (*list)->rightPointers[i] = i + 1;
    }
    (*list)->rightPointers[LIST_MAX_SIZE - 1] = 0;
}

bool pushBack(List* list, ListElem elem){
    if (list->freeElement == 0) {
        printf("Unable to push: list is full\n");
        return false;
    }
    int nextFreeElement = list->rightPointers[list->freeElement];
    list->elements[list->freeElement] = elem;
    list->rightPointers[list->freeElement] = 0;
    if (list->head == 0) {
        list->leftPointers[list->freeElement] = 0;
        list->head = list->freeElement;
    } else {
        list->leftPointers[list->freeElement] = list->tail;
        list->rightPointers[list->tail] = list->freeElement;
    }
    list->tail = list->freeElement;
    list->freeElement = nextFreeElement;
    //printf("%s\n", __func__);
    return true;
}

bool popBack(List* list, ListElem* elem){
    if (list->tail == 0) {
        printf("Unable to pop: list is empty\n");
        return false;
    }
    if (elem != NULL) *elem = list->elements[list->tail];
    list->rightPointers[list->tail] = list->freeElement;
    list->freeElement = list->tail;
    list->tail = list->leftPointers[list->tail];
    if (list->tail == 0) list->head = 0;
    else list->rightPointers[list->tail] = 0;
    return true;
}

bool insert(List* list, int pos, ListElem elem){
    if (list->freeElement == 0) {
        printf("Unable to insert: list is full\n");
        return false;
    }
    int index = list->head;
    while (index != 0 && pos > 0) {
        index = list->rightPointers[index];
        --pos;
    }
    if (index == 0) {
        if (pos == 0) {
            return pushBack(list, elem);
        } else {
            printf("List index out of range\n");
            return false;
        }
    }
    printf("%d\n", index);
    int nextFreeElement = list->rightPointers[list->freeElement];
    list->elements[list->freeElement] = elem;
    list->rightPointers[list->freeElement] = index;
    list->leftPointers[list->freeElement] = list->leftPointers[index];
    if (list->leftPointers[index] != 0) list->rightPointers[list->leftPointers[index]] = list->freeElement;
    else list->head = list->freeElement;
    list->leftPointers[index] = list->freeElement;
    list->freeElement = nextFreeElement;
    return true;
}

bool erase(List* list, int pos) {
    if (list->head == 0) {
        printf("Unable to erase: list is empty\n");
        return false;
    }
    int index = list->head;
    while (index != 0 && pos > 0) {
        index = list->rightPointers[index];
        --pos;
    }
    if (index == 0) {
        printf("List index out of range\n");
        return false;
    }
    if (list->head == list->tail) {
        list->rightPointers[list->head] = list->freeElement;
        list->freeElement = list->head;
        list->head = 0;
        list->tail = 0;
    } else {
        if (list->leftPointers[index] != 0) list->rightPointers[list->leftPointers[index]] = list->rightPointers[index];
        else list->head = list->rightPointers[index];
        if (list->rightPointers[index] != 0) list->leftPointers[list->rightPointers[index]] = list->leftPointers[index];
        else list->tail = list->leftPointers[index];
        list->rightPointers[index] = list->freeElement;
        list->freeElement = index;
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

void consoleDump(List* list){
    printf("Head: %d; Tail: %d; FreeElem: %d\n", list->head, list->tail, list->freeElement);
    printf("Elements:       \t");
    for (int i = 0; i < LIST_MAX_SIZE; ++i) {
        printElement(list->elements[i]);
        putchar('\t');
    }
    printf("\nRight index pointers:\t");
    for (int i = 0; i < LIST_MAX_SIZE; ++i) {
        printf("%d\t", list->rightPointers[i]);
    }
    printf("\nLeft index pointers:\t");
    for (int i = 0; i < LIST_MAX_SIZE; ++i) {
        printf("%d\t", list->leftPointers[i]);
    }
    putchar('\n');
}