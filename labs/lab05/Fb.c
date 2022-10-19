// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

typedef struct adjNode *AdjList;
struct adjNode {
    int v;
    AdjList next;
};

// DO NOT modify this struct
struct fb {
    int numPeople;
    int capacity;

    char **names; // the id of a person is simply the index
                  // that contains their name in this array
    
    Map nameToId; // maps names to ids

    AdjList *adj; // adjacency lists, kept in increasing order
};

static void  increaseCapacity(Fb fb);
static char *myStrdup(char *s);
static int   nameToId(Fb fb, char *name);

static AdjList adjListInsert(AdjList l, int v);
static AdjList newAdjNode(int v);
static bool inAdjList(AdjList l, int v);
static void freeAdjList(AdjList l);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb   FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->capacity = DEFAULT_CAPACITY;
    
    fb->names = calloc(fb->capacity, sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fb->nameToId = MapNew();

    fb->adj = calloc(fb->capacity, sizeof(AdjList));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->capacity; i++) {
        freeAdjList(fb->adj[i]);
    }
    free(fb->adj);

    MapFree(fb->nameToId);

    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }
    free(fb->names);
    
    free(fb);
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == fb->capacity) {
        increaseCapacity(fb);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = myStrdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

static void increaseCapacity(Fb fb) {
    int newCapacity = fb->capacity * 2;
    
    fb->names = realloc(fb->names, newCapacity * sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->names[i] = NULL;
    }
    
    fb->adj = realloc(fb->adj, newCapacity * sizeof(AdjList));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->adj[i] = NULL;
    }
    
    fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (!inAdjList(fb->adj[id1], id2)) {
        fb->adj[id1] = adjListInsert(fb->adj[id1], id2);
        fb->adj[id2] = adjListInsert(fb->adj[id2], id1);
        return true;
    } else {
        return false;
    }
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return inAdjList(fb->adj[id1], id2);
}

int  FbNumFriends(Fb fb, char *name) {
    int id = nameToId(fb, name);
    
    int numFriends = 0;
    for (AdjList curr = fb->adj[id]; curr != NULL; curr = curr->next) {
        numFriends++;
    }
    return numFriends;
}

////////////////////////////////////////////////////////////////////////
// Your tasks

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    int name1Id = nameToId(fb,name1);
    int name2Id = nameToId(fb,name2);
    if(!FbIsFriend(fb,name1,name2)){
        return false;
    }
    AdjList curr = fb->adj[name1Id];
    while(curr ->next -> v != name2Id){
        curr = curr->next;
    }
    AdjList tmp = curr -> next;
    curr -> next = curr -> next -> next;
    free(tmp); // free the deleted node

    curr = fb->adj[name2Id];
    while(curr ->next -> v != name1Id){
        curr = curr->next;
    }
    tmp = curr -> next;
    curr -> next = curr -> next -> next;
    free(tmp); // free the deleted node
    return true;
}

List FbMutualFriends(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    List l = ListNew();
    return l;
}

void FbFriendRecs1(Fb fb, char *name) {
    // TODO: Complete this function
}

////////////////////////////////////////////////////////////////////////
// Optional task

void FbFriendRecs2(Fb fb, char *name) {
    // TODO: Complete this function
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

static AdjList adjListInsert(AdjList l, int v) {
    if (l == NULL || v < l->v) {
        AdjList new = newAdjNode(v);
        new->next = l;
        return new;
    } else if (v == l->v) {
        return l;
    } else {
        l->next = adjListInsert(l->next, v);
        return l;
    }
}

static AdjList newAdjNode(int v) {
    AdjList n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->v = v;
    n->next = NULL;
    return n;
}

static bool inAdjList(AdjList l, int v) {
    for (AdjList n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static void freeAdjList(AdjList l) {
    AdjList n = l;
    while (n != NULL) {
        AdjList temp = n;
        n = n->next;
        free(temp);
    }
}

