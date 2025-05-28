// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>

#include "../src/engine/util.h"
#include "../src/engine/errors.h"

static i8 alloc_count = 0;
static i8 passedTests = 0;
static const u8 totalTests = 5;

void *my_malloc(size_t size) {
    alloc_count++;
    return malloc(size);
}

void my_free(void *ptr) {
    if (ptr) alloc_count--;
    free(ptr);
}

#define malloc(size) my_malloc(size)
#define free(ptr) my_free(ptr)

u8 testInit() {
    Vector vec;
    u8 status;

    printf("Test 1/%d: Vector initialization.\n", totalTests);
    status = vectorInit(&vec);
    vectorDestroy(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }
    printf("PASS: Vector initialized successfully!\n");
    return 0;
}

u8 testNullPointerInit() {
    Vector *vec = NULL;
    u8 status;

    printf("Test 2/%d: Null pointer initialization.\n", totalTests);
    status = vectorInit(vec);
    if (status != VECTOR_NULL_POINTER) {
        printf("FAIL: Expected VECTOR_NULL_POINTER, got %d\n", status);
        return 1;
    }
    printf("PASS: Null pointer initialization correctly returned VECTOR_NULL_POINTER.\n");
    return 0;
}

u8 testEmptyVectorDestroy() {
    Vector vec;
    u8 status;

    printf("Test 3/%d: Destroy empty vector.\n", totalTests);
    status = vectorDestroy(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to destroy empty vector: status code %d\n", status);
        return 1;
    }
    printf("PASS: Empty vector destroyed successfully!\n");
    return 0;
}

u8 testPushItem() {
    Vector vec;
    u8 status;

    printf("Test 4/%d: Push item to vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    int *item = malloc(sizeof(int));
    *item = 42;
    status = vectorPush(&vec, item);
    // This is here since under the hood, realloc will make an additional call of malloc, which we don't want to count as an allocation for the item itself.
    // Since the pointer is shared and will be freed by vectorDestroy, we don't want to count it as an allocation.
    --alloc_count;
    
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to push item to vector: status code %d\n", status);
        vectorDestroy(&vec);
        return 1;
    }
    if (vec.size != 1 || vec.items[0] != item) {
        printf("FAIL: Vector size or item mismatch after push.\n");
        vectorDestroy(&vec);
        return 1;
    }
    printf("PASS: Item pushed to vector successfully!\n");
    passedTests++;
    vectorDestroy(&vec);
    
    return 0;
}

u8 testMemoryLeak() {
    printf("Test 99/%d: Memory leak check.\n", alloc_count);
    if (alloc_count != 0) {
        printf("FAIL: Memory leak detected! Allocations not freed: Allocation net %d\n", alloc_count);
        return 1;
    }
    printf("PASS: No memory leaks detected!\n");
    return 0;
}


int main(int argc, char** argv) {
    printf("Running vector tests...\n");
    if (!testInit()) return 1; else passedTests++;
    if (!testNullPointerInit()) return 1; else passedTests++;
    if (!testEmptyVectorDestroy()) return 1; else passedTests++;
    if (!testPushItem()) return 1; else passedTests++;


    if (!testMemoryLeak()) return 1; else passedTests++;
    
    printf("All tests completed.\n");
    printf("Tests passed: %d/%d; Percent passed: %d\n", passedTests, totalTests, (passedTests * 100) / totalTests);
    return 0;
}
