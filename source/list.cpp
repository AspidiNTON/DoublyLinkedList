#include "list.h"

const int LIST_MAX_SIZE = 15;

struct List {
    ListElem elements[LIST_MAX_SIZE];
    int rightPointers[LIST_MAX_SIZE];
    int leftPointers[LIST_MAX_SIZE];
    int freeElement;
};

void initList(List** list){
    *list = (List*)calloc(1, sizeof(List));
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
    if (list->rightPointers[0] == 0) {
        list->leftPointers[list->freeElement] = 0;
        list->rightPointers[0] = list->freeElement;
    } else {
        list->leftPointers[list->freeElement] = list->leftPointers[0];
        list->rightPointers[list->leftPointers[0]] = list->freeElement;
    }
    list->leftPointers[0] = list->freeElement;
    list->freeElement = nextFreeElement;
    //printf("%s\n", __func__);
    return true;
}

bool popBack(List* list, ListElem* elem){
    if (list->leftPointers[0] == 0) {
        printf("Unable to pop: list is empty\n");
        return false;
    }
    if (elem != NULL) *elem = list->elements[list->leftPointers[0]];
    list->rightPointers[list->leftPointers[0]] = list->freeElement;
    list->freeElement = list->leftPointers[0];
    list->leftPointers[0] = list->leftPointers[list->leftPointers[0]];
    if (list->leftPointers[0] == 0) list->rightPointers[0] = 0;
    else list->rightPointers[list->leftPointers[0]] = 0;
    return true;
}

bool insert(List* list, int pos, ListElem elem){
    if (list->freeElement == 0) {
        printf("Unable to insert: list is full\n");
        return false;
    }
    int index = list->rightPointers[0];
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
    else list->rightPointers[0] = list->freeElement;
    list->leftPointers[index] = list->freeElement;
    list->freeElement = nextFreeElement;
    return true;
}

bool erase(List* list, int pos) {
    if (list->rightPointers[0] == 0) {
        printf("Unable to erase: list is empty\n");
        return false;
    }
    int index = list->rightPointers[0];
    while (index != 0 && pos > 0) {
        index = list->rightPointers[index];
        --pos;
    }
    if (index == 0) {
        printf("List index out of range\n");
        return false;
    }
    if (list->rightPointers[0] == list->leftPointers[0]) {
        list->rightPointers[list->rightPointers[0]] = list->freeElement;
        list->freeElement = list->rightPointers[0];
        list->rightPointers[0] = 0;
        list->rightPointers[0] = 0;
    } else {
        if (list->leftPointers[index] != 0) list->rightPointers[list->leftPointers[index]] = list->rightPointers[index];
        else list->rightPointers[0] = list->rightPointers[index];
        if (list->rightPointers[index] != 0) list->leftPointers[list->rightPointers[index]] = list->leftPointers[index];
        else list->rightPointers[0] = list->leftPointers[index];
        list->rightPointers[index] = list->freeElement;
        list->freeElement = index;
    }
    return true;
}

void printList(List* list){
    int id = list->rightPointers[0];
    while (id != 0) {
        printElement(list->elements[id]);
        putchar(' ');
        id = list->rightPointers[id];
    }
    putchar('\n');
}

void consoleDump(List* list){
    printf("Head: %d; Tail: %d; FreeElem: %d\n", list->rightPointers[0], list->leftPointers[0], list->freeElement);
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

bool createDotFile(List* list, const char* outFilename){
    if (outFilename == NULL) {
        printf("Filename nullptr recieved\n");
        return false;
    }
    FILE* filePtr = fopen(outFilename, "w");
    if (filePtr == NULL) {
        printf("Unable to open file\n");
        return false;
    }
    //beginning and vertices declaration
    fprintf(filePtr, "digraph list{\nrankdir=LR\n\tFREE\n");
    for (int i = 0; i < LIST_MAX_SIZE; ++i) {
        fprintf(filePtr, "\tx%d [shape=record,style=rounded,label=\"id: %d | data: ", i, i);
        fprintElement(filePtr, list->elements[i]);
        fprintf(filePtr, " | next: %d | prev: %d\"]\n", list->rightPointers[i], list->leftPointers[i]);
    }
    //next arrows
    fprintf(filePtr, "\tedge[color=blue]\n");
    int index = 0;
    do {
        fprintf(filePtr, "\tx%d->x%d\n", index, list->rightPointers[index]);
        index = list->rightPointers[index];
    } while (index != 0);
    //prev arrows
    fprintf(filePtr, "\tedge[color=red]\n");
    index = 0;
    do {
        fprintf(filePtr, "\tx%d->x%d\n", index, list->leftPointers[index]);
        index = list->leftPointers[index];
    } while (index != 0);
    //free memory
    fprintf(filePtr, "\tedge[color=green]\n");
    index = list->freeElement;
    while (list->rightPointers[index] != 0) {
        fprintf(filePtr, "\tx%d->x%d\n", index, list->rightPointers[index]);
        index = list->rightPointers[index];
    }
    fprintf(filePtr, "\tFREE->x%d\n", list->freeElement);
    putc('}', filePtr);
    fclose(filePtr);
    return true;
}

bool createSvgFromDot(const char* inFilename, const char* outFilename){
    if (inFilename == NULL || outFilename == NULL) {
        printf("Filename nullptr recieved\n");
        return false;
    }
    char command[100] = {};
    sprintf(command, "dot -Tsvg %s -o %s", inFilename, outFilename);
    if (system(command) != 0) {
        printf("Image creation command failed\n");
        return false;
    }
    return true;
}