#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ListElem;

struct List;

void initList(List** list);

bool pushBack(List* list, ListElem elem);

void printElement(ListElem elem);

void printList(List* list);


#endif