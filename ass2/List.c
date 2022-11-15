// Implementation of the String List ADT

// taken from file List.c from lab05

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"




static Node newNode(char *s);
static char *myStrdup(char *s);
static int qsortStrcmp(const void *ptr1, const void *ptr2);

////////////////////////////////////////////////////////////////////////

// Creates a new empty list
List ListNew(void) {
    List l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

// Frees all memory allocated for the given list
void ListFree(List l) {
    Node curr = l->head;
    while (curr != NULL) {
        Node temp = curr;
        curr = curr->next;
        free(temp->s);
        free(temp);
    }
    free(l);
}

// Adds a string to the end of the list
void ListAppend(List l, char *s) {
    Node n = newNode(s);
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;
}

static Node newNode(char *s) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    n->s = myStrdup(s);
    n->next = NULL;
    return n;
}

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Returns the number of items in the list
int  ListSize(List l) {
    return l->size;
}

// Sorts the list in ASCII order
void ListSort(List l) {
    char **items = malloc(l->size * sizeof(char *));
    if (items == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    for (Node curr = l->head; curr != NULL; curr = curr->next) {
        items[i++] = curr->s;
    }
    qsort(items, l->size, sizeof(char *), qsortStrcmp);
    i = 0;
    for (Node curr = l->head; curr != NULL; curr = curr->next) {
        curr->s = items[i++];
    }
    free(items);
}

static int qsortStrcmp(const void *ptr1, const void *ptr2) {
    char *s1 = *(char **)ptr1;
    char *s2 = *(char **)ptr2;
    return strcmp(s1, s2);
}

// Prints the list, one string per line
// If the strings themselves contain newlines, too bad
void ListPrint(List l) {
    for (Node n = l->head; n != NULL; n = n->next) {
        printf("%s\n", n->s);
    }
}

int ListGetIndex(List l,char *s){
    int count = 0;
    for(Node n = l->head; n != NULL; n = n->next,count++){
        if(strcmp(s,n -> s) == 0){
            return count;
        }
    }
    return -1;
}

char *ListGetString(List l,int index){
    int i = 0;
    for(Node n = l->head; n != NULL; n = n->next,i++){
        if(i == index){
            return n->s;
        }
    }
    return NULL;
}
