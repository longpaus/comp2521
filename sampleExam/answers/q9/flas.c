
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    List flas = NULL;
    int flasLen = 0;

    List curr = l;
    while (curr != NULL) {
        List start = curr;
        int len = 1;

        while (curr->next != NULL && curr->next->value > curr->value) {
            len++;
            curr = curr->next;
        }

        if (len > flasLen && len >= 2) {
            flas = start;
            flasLen = len;
        }
        curr = curr->next;
    }

    return flas;
}

