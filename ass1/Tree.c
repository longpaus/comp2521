// Implementation of the Tree ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
	Record rec;
	Node left;
	Node right;

	// IMPORTANT: Do not modify the fields above
	// You may add additional fields below if necessary
	int height;
};

struct tree {
	Node root;
	int (*compare)(Record, Record);

	// IMPORTANT: Do not modify the fields above
	// You may add additional fields below if necessary
};

static void doTreeFree(Node n, bool freeRecords);
static int getHeight(Node n);
static Node newNode(Record rec);
static int max(int x, int y);
static Node rotateRight(Node n1);
static Node rotateLeft(Node n2);
static Node avlInsert(Tree t, Record rec, Node n);
static bool isInTree(Tree t,Record rec,Node n);

////////////////////////////////////////////////////////////////////////
// Provided functions
// !!! DO NOT MODIFY THESE FUNCTIONS !!!

Tree TreeNew(int (*compare)(Record, Record)) {
	Tree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	t->root = NULL;
	t->compare = compare;
	return t;
}

void TreeFree(Tree t, bool freeRecords) {
	doTreeFree(t->root, freeRecords);
	free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
	if (n != NULL) {
		doTreeFree(n->left, freeRecords);
		doTreeFree(n->right, freeRecords);
		if (freeRecords) {
			RecordFree(n->rec);
		}
		free(n);
	}
}

////////////////////////////////////////////////////////////////////////
// Functions you need to implement

bool TreeInsert(Tree t, Record rec) {
	if (TreeSearch(t, rec) == NULL) {
		return false;
	}
    t -> root = avlInsert(t,rec,t -> root);
    return true;
}
static int getHeight(Node n) {
	if (n == NULL) {
		return 0;
	}
	return n->height;
}

//took from lab04
static Node newNode(Record rec) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	n->left = NULL;
	n->right = NULL;
	n->rec = rec;
	n->height = 1;
	return n;
}

static int max(int x, int y) {
	return (x > y) ? x : y;
}

//from the lecture code
static Node rotateRight(Node n1) {
	if (n1 == NULL || n1->left == NULL) {
		return n1;
	}
	Node n2 = n1->left;
	n1->left = n2->right;
	n2->right = n1;

	n1->height = max(getHeight(n1->left), getHeight(n1->right)) + 1;
	n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
	return n2;
}

//from lecture code
static Node rotateLeft(Node n2) {
	if (n2 == NULL || n2->right == NULL){
		return n2;
	}
	Node n1 = n2->right;
	n2->right = n1->left;
	n1->left = n2;

    n2 -> height = max(getHeight(n2 -> left),getHeight(n2 -> right)) + 1;
    n1 -> height = max(getHeight(n1 -> left), getHeight(n1 -> right)) + 1;
	return n1;
}

static Node avlInsert(Tree t, Record rec, Node n) {
	if (n == NULL) {
		return newNode(rec);
	}
	if (t->compare(rec, n->rec) == -1) {
		n->left = avlInsert(t, rec, n->left);
	} else if (t->compare(rec, n->rec) == 1) {
		n->right = avlInsert(t, rec, n->right);
	} else {
		return n;
	}
	n->height = 1 + max(getHeight(n->left), getHeight(n->right));
	int bf = (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
	if (bf > 1) {
        if(t->compare(rec,n -> left->rec) == 1){
            n -> left = rotateLeft(n -> left);
            return rotateRight(n);
        }
        return rotateRight(n);
	}
    else if(bf < -1){
        if(t->compare(rec,n->right->rec) == -1){
            n -> right = rotateRight(n -> right);
        }
        return rotateLeft(n);
    }
    return n;
}

Record TreeSearch(Tree t, Record rec) {
    return (isInTree(t,rec,t->root)) ? rec : NULL;
}

//return true if rec is in tree, false if rec is not in the tree
static bool isInTree(Tree t,Record rec,Node n){
    if(n == NULL){
        return false;
    }
    else if(t -> compare(rec,n-> rec) == -1){
        isInTree(t,rec,n -> left);
    }
    else if(t -> compare(rec,n -> rec) == 1){
        isInTree(t,rec,n -> right);
    }
    else{
        return true;
    }
}

List TreeSearchBetween(Tree t, Record lower, Record upper) {
	return ListNew();
}

Record TreeNext(Tree t, Record rec) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////
