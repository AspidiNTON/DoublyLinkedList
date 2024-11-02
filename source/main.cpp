#include "list.h"

void printElement(ListElem elem){
    printf("%d", elem);
}

void fprintElement(FILE* filePtr, ListElem elem){
    if (filePtr == NULL) {
        printf("File nullptr recieved\n");
    } else fprintf(filePtr, "%d", elem);
}


int main(){
    List* list = {};
    initList(&list);

    pushBack(list, 5);
    pushBack(list, 16);
    pushBack(list, 226);
    pushBack(list, 655);
    pushBack(list, 90);
    pushBack(list, 14);
    pushBack(list, 32);
    pushBack(list, 999);
    pushBack(list, 666666);
    pushBack(list, 324);
    pushBack(list, 1488);
    popBack(list, NULL);
    popBack(list, NULL);
    popBack(list, NULL);
    popBack(list, NULL);
    popBack(list, NULL);
    pushBack(list, 324);
    pushBack(list, 1488);
    
    insert(list, 3, 4444);

    printList(list);
    consoleDump(list);


    erase(list, 4);
    printList(list);
    consoleDump(list);
    
    createDotFile(list, "result.dot");
    createSvgFromDot("result.dot", "output.svg");
    return 0;
}