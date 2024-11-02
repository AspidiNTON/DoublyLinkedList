#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ListElem;

struct List;

void initList(List** list);

bool pushBack(List* list, ListElem elem);

bool popBack(List* list, ListElem* elem);

bool insert(List* list, int pos, ListElem elem);

bool erase(List* list, int pos);

void printElement(ListElem elem);

void fprintElement(FILE* filePtr, ListElem elem);

void printList(List* list);

void consoleDump(List* list);

bool createDotFile(List* list, const char* outFilename);

bool createSvgFromDot(const char* inFilename, const char* outFilename);


#endif