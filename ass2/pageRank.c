// COMP2521 Assignment 2

// Written by:
// Date:

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

List getCollection();

#define MAX_URL_LEN 1024

int main(int argc, char *argv[]) {
    // argc is the number of command-line arguments, which includes the
    // program name
    // // argv is the array of command-line arguments
    // if (argc != 4) {
    //     fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
    //             argv[0]);
    //     return EXIT_FAILURE;
    // }

    // Command-line arguments are received as strings. They can be converted
    // to number types using atoi and atof.
    // double d = atof(argv[1]);
    // double diffPR = atof(argv[2]);
    // int maxIterations = atoi(argv[3]);
    getCollection();
}

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


