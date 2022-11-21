
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	if (t == NULL) {
		BSTree n = malloc(sizeof(*n));

		n->value = val;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	if (val < t->value) {
		t->left = BSTreeInsertR(t->left, val);
	}
	if (val > t->right) {
		t->right = BSTreeInsertR(t->right, val);
	}
	return t;
}
