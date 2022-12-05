
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"


static void ListAddElement(List l,int val);
static void cpyList(List l1,List l2);

List findShortestSublist(List l, int start, int end) {
    int curr = 0;
    int shortest = 0;
    List shortestSeq = ListNew();

    for(Node i = l->first; i != NULL; i = i ->next){
        if(i->value == start){
            List seq = ListNew();
            seq->first = i;
            seq -> last = i;
            curr = 0;

            for(Node j = i; j != NULL; j = j -> next){
                ListAddElement(seq,j->value);
                curr++;
                if(j-> value == end){
                    if(curr < shortest){
                        shortest = curr;
                        ListFree(shortestSeq);
                        List shortestSeq = ListNew();
                        cpyList(shortestSeq,seq);
                    }
                    break;
                }
            }
            ListFree(seq);
        }
    }

    return shortestSeq;
}
//copy l2 into l1
static void cpyList(List l1,List l2){
    for(Node i = l2->first; i != NULL; i = i -> next){
        ListAddElement(l1,i->value);
    }
}

static void ListAddElement(List l,int val){
    if(l -> first == NULL){
        l -> first = newNode(val);
        l -> last = l -> first;
    }
    Node n = newNode(val);
    l->last ->next =  n;
    l -> last = n;
    l -> last -> next = NULL;
}

