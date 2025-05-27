#include "util.h"

void listInit(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

