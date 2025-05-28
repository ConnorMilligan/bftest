#include <stdlib.h>

#include "util.h"
#include "errors.h"

void listInit(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

u8 listDestroy(List *list) {
    Node *current = list->head;
    Node *nextNode;

    if (list == NULL) {
        return LIST_NULL_POINTER; // List pointer is NULL
    }

    if (list->head == NULL) {
        return LIST_SUCCESS; // List is already empty
    }

    while (current != NULL) {
        nextNode = current->next; // Store the next node
        free(current);            // Free the current node
        current = nextNode;       // Move to the next node
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return LIST_SUCCESS; // Success
}

u8 listPush(List *list, void *data) {
    Node *node = malloc(sizeof(Node));

    if (node == NULL) {
        return LIST_MEMORY_ERROR; // Memory allocation failed
    }

    if (list == NULL) {
        free(node);
        return LIST_NULL_POINTER; // List pointer is NULL
    }

    node->data = data;
    node->next = list->head;
    list->head = node;

    if (list->size == 0) list->tail = node;

    list->size++;

    return LIST_SUCCESS; // Success
}


u8 listDelete(List *list, usize index) {
    Node *current = list->head;
    Node *previous = NULL;
    usize i = 0;

    if (index >= list->size) {
        return LIST_OUT_OF_BOUNDS; // Index out of bounds
    }

    while (current != NULL) {
        if (i == index) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                list->head = current->next; // Deleting the head
            }

            if (current->next == NULL) {
                list->tail = previous; // Deleting the tail
            }

            free(current);
            list->size--;
            return LIST_SUCCESS; // Success
        }
        previous = current;
        current = current->next;
        i++;
    }

    return LIST_NOT_FOUND; // Not found
}

Node* listPop(List *list) {
    Node *returnNode;

    if (list->head == NULL) {
        return NULL; // List is empty
    }

    returnNode = list->head;
    list->head = returnNode->next;

    if (list->head == NULL) {
        list->tail = NULL; // List is now empty
    }

    list->size--;
    return returnNode;
}

Node* listGet(List *list, usize index) {
    Node *current = list->head;
    usize i = 0;

    if (index >= list->size) {
        return NULL; // Index out of bounds
    }

    while (current != NULL) {
        if (i == index) {
            return current;
        }
        current = current->next;
        i++;
    }

    return NULL; // Not found
}