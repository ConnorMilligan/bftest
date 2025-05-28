#include <stdlib.h>

#include "util.h"
#include "errors.h"

static u8 vectorResize(Vector *vec, usize capcity) {
    void **items = realloc(vec->items, sizeof(void *) * capcity);
    if (items) {
        vec->items = items;
        vec->capacity = capcity;
        return VECTOR_SUCCESS;
    }
    return VECTOR_MEMORY_ALLOCATION;
}

u8 vectorInit(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_NULL_POINTER;
    }

    vec->items = malloc(VECTOR_INIT_CAPACITY * sizeof(void *));
    if (vec->items == NULL) {
        return VECTOR_MEMORY_ALLOCATION;
    }
    
    vec->size = 0;
    vec->capacity = VECTOR_INIT_CAPACITY;
    
    return VECTOR_SUCCESS;
}

u8 vectorPush(Vector *vec, void *item) {
    if (vec == NULL) {
        return VECTOR_NULL_POINTER;
    }

    // Check if we need to resize the vector
    if (vec->size >= vec->capacity)
        if (vectorResize(vec, vec->capacity*2) != VECTOR_SUCCESS)
            return VECTOR_MEMORY_ALLOCATION;
        
    vec->items[vec->size++] = item;
    return VECTOR_SUCCESS;
}

u8 vectorDestroy(Vector *vec) {
    if (vec == NULL) {
        return VECTOR_EMPTY;
    }

    // Free each item in the vector if it is not NULL
    for (usize i = 0; i < vec->size; i++) {
        if (vec->items[i] != NULL) {
            free(vec->items[i]);
        }
    }

    // Free the data array itself
    free(vec->items);
    vec->items = NULL;
    vec->size = 0;
    vec->capacity = 0;

    return VECTOR_SUCCESS;
}