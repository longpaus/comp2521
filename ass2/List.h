// Interface to the String List ADT

// taken from file List.h from lab05

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list *List;

// Creates a new empty list
// Complexity: O(1)
List ListNew(void);

// Frees all memory allocated for the given list
// Complexity: O(n)
void ListFree(List l);

// Adds a string to the end of the list. Makes a copy of the string
// before adding it to the list.
// Complexity: O(1)
void ListAppend(List l, char *s);

// Returns the number of items in the list
// Complexity: O(1)
int  ListSize(List l);

// Sorts the list in ASCII order
// Average complexity: O(n log n)
void ListSort(List l);

// Prints the list, one string per line
// If the strings themselves contain newlines, too bad
void ListPrint(List l);


#endif

