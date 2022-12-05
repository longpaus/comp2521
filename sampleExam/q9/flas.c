
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    List longest= NULL;
    int curr;
    int longestCount = 0;
    for(List i = l; i != NULL; i = i -> next){
        List k = i -> next;
        curr = 0;
        
        for(List j = i; k != NULL; j = j ->next,k = k -> next){
            if(k -> value > j -> value){
                curr++;
            }else{
                break;
            }
            if(curr > longestCount){
                longestCount = curr;
                longest = i;
            }

        }
    }
    return longest;
}

