
#include <stdio.h>

#include "List.h"

#define MAX_URL_LEN 1024
List getCollection(){
    FILE *f = fopen("collection.txt","r");
    char x[MAX_URL_LEN];
    List l = ListNew();
    while (fscanf(f, " %1023s", x) == 1) {
        ListAppend(l,x);
    }
    ListPrint(l);
    return l;
}




