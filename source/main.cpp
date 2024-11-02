#include "list.h"

void printElement(ListElem elem){
    printf("%d", elem);
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
    printList(list);
    return 0;
}