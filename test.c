#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void change(bool *h){
    *h = false;
}

int main(){
    
    bool *h = malloc(sizeof(bool));
    *h = true;
    printf("%d\n",*h);
    change(h);
    printf("%d\n",*h);
    free(h);
    
}

