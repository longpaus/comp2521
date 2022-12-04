
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

static void doMinDiff(BSTree t, int l, bool *firstVal, int *prev, int *min);

int minDiff(BSTree t, int l) {
    // TODO
    bool firstVal = true;
    int prev = 0;
    int min = 0;
    doMinDiff(t, l, &firstVal, &prev, &min);
    return min;
}

static void doMinDiff(BSTree t, int l, bool *firstVal, int *prev, int *min) {
    if (t == NULL) {
        return;
    }
    if (l == 0) {
        if (*firstVal) {
            *prev = t->key;
            *firstVal = false;
        } else {
            if (*min == 0 || t->key - *prev < *min) {
                *min = t->key - *prev;
            }
            *prev = t->key;
        }
        return;
    }
    doMinDiff(t->left, l - 1, firstVal, prev, min);
    doMinDiff(t->right, l - 1, firstVal, prev, min);
}

