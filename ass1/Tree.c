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
static Node avlInsert(Tree t, Record rec, Node n, bool *inserted);
static bool isInTree(Tree t, Record rec, Node n);
static Record doTreeNext(Tree t, Record rec, Node n);
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper,
                                List l);

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
	bool inserted = false;
	t->root = avlInsert(t, rec, t->root, &inserted);
	return inserted;
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
	//rotate right
	Node n2 = n1->left;
	n1->left = n2->right;
	n2->right = n1;

	//updating the height
	n1->height = max(getHeight(n1->left), getHeight(n1->right)) + 1;
	n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
	return n2;
}

//from lecture code
static Node rotateLeft(Node n2) {
	if (n2 == NULL || n2->right == NULL) {
		return n2;
	}
	//rotate left
	Node n1 = n2->right;
	n2->right = n1->left;
	n1->left = n2;

	//updating the height
	n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
	n1->height = max(getHeight(n1->left), getHeight(n1->right)) + 1;
	return n1;
}

static Node avlInsert(Tree t, Record rec, Node n, bool *inserted) {
	if (n == NULL) {
		*inserted = true;
		return newNode(rec);
	}
	if (t->compare(rec, n->rec) == -1) {
		n->left = avlInsert(t, rec, n->left, inserted);
	} else if (t->compare(rec, n->rec) == 1) {
		n->right = avlInsert(t, rec, n->right, inserted);
	} else {
		return n;
	}
	n->height = 1 + max(getHeight(n->left), getHeight(n->right));
	int bf = (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
	if (bf > 1) {
		if (t->compare(rec, n->left->rec) == 1) {
			n->left = rotateLeft(n->left);
		}
		return rotateRight(n);
	} else if (bf < -1) {
		if (t->compare(rec, n->right->rec) == -1) {
			n->right = rotateRight(n->right);
		}
		return rotateLeft(n);
	}
	return n;
}

Record TreeSearch(Tree t, Record rec) {
	return (isInTree(t, rec, t->root)) ? rec : NULL;
}

//return true if rec is in tree, false if rec is not in the tree
static bool isInTree(Tree t, Record rec, Node n) {
	if (n == NULL) {
		return false;
	} else if (t->compare(rec, n->rec) == -1) {
		isInTree(t, rec, n->left);
	} else if (t->compare(rec, n->rec) == 1) {
		isInTree(t, rec, n->right);
	}

	return true;
}

List TreeSearchBetween(Tree t, Record lower, Record upper) {
	List l = ListNew();
	doTreeSearchBetween(t, t->root, lower, upper, l);
	return l;
}

//from lab04
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper,
                                List l) {
	if (n == NULL) {
		return;
	}
	if (t->compare(n->rec, lower) == 1) {
		doTreeSearchBetween(t, n->left, lower, upper, l);
	}
	if (t->compare(n->rec, lower) >= 0 && t->compare(n->rec, upper) <= 0) {
		ListAppend(l, n->rec);
	}
	if (t->compare(n->rec, upper) == -1) {
		doTreeSearchBetween(t, n->right, lower, upper, l);
	}
}

Record TreeNext(Tree t, Record rec) {
	return doTreeNext(t, rec, t->root);
}
/*
search for the smallest record that is larger than rec then return it.
return NULL if there is no such record.
*/
static Record doTreeNext(Tree t, Record rec, Node n) {
	if (n == NULL) {
		return NULL;
	}
	if (t->compare(n->rec, rec) >= 0) {
		if (n->left == NULL || t->compare(n->left->rec, rec) == -1) {
			return n->rec;
		}
	}
	if (t->compare(n->rec, rec) <= 0) {
		return doTreeNext(t, rec, n->right);
	} else {
		return doTreeNext(t, rec, n->left);
	}
}

////////////////////////////////////////////////////////////////////////
