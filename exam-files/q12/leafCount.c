
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"


void doLeafCount(BSTree t, int len, int level,int *count);

int leafCount(BSTree t, int pathLength) {
    
    int count = 0;
    doLeafCount(t,pathLength,0,&count);
    return count;
}

void doLeafCount(BSTree t, int len, int level,int *count){
    if(t -> left == NULL && t -> right == NULL){
        if(level >= len){
            *count = *count + 1;
        }
        return;
    }
    if(t -> left != NULL){
        doLeafCount(t -> left,len,level + 1,count);
    }
    if(t -> right != NULL)
        doLeafCount(t -> right,len,level + 1,count);
}

