// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>

#include "../src/engine/util.h"
#include "../src/engine/errors.h"

static i8 passedTests = 0;
static const u8 totalTests = 9;

u8 testUninitializedVector() {
    Vector vec;
    u8 status;

    printf("Test 1/%d: Uninitialized vector destroy.\n", totalTests);
    // Not initializing the vector, so it should return VECTOR_UNINITIALIZED
    status = vectorDestroy(&vec);
    if (status != VECTOR_UNINITIALIZED) {
        printf("FAIL: Expected VECTOR_UNINITIALIZED, got %d\n", status);
        return 1;
    }
    printf("PASS: Uninitialized vector destroy correctly returned VECTOR_UNINITIALIZED.\n");
    return 0;
}

u8 testInit() {
    Vector vec;
    u8 status;

    printf("Test 2/%d: Vector initialization.\n", totalTests);
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

    printf("Test 3/%d: Null pointer initialization.\n", totalTests);
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

    printf("Test 4/%d: Destroy empty vector.\n", totalTests);
    status = vectorInit(&vec);
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

    printf("Test 5/%d: Push item to vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    int *item = malloc(sizeof(int));
    *item = 42;
    status = vectorPush(&vec, item);
    
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
    vectorDestroy(&vec);
    
    return 0;
}

u8 testPop() {
    Vector vec;
    u8 status;

    printf("Test 6/%d: Pop item from vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    // Push an item to pop it later
    int *item = malloc(sizeof(int));
    *item = 42;
    status = vectorPush(&vec, item);
    
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to push item to vector: status code %d\n", status);
        vectorDestroy(&vec);
        return 1;
    }

    int *poppedItem = vectorPop(&vec);
    if (poppedItem == NULL || *poppedItem != 42) {
        printf("FAIL: Popped item mismatch. Expected 42, got %d\n", poppedItem ? *poppedItem : -1);
        free(poppedItem); // Free the popped item if it was allocated
        vectorDestroy(&vec);
        return 1;
    }
    
    free(poppedItem); // Free the popped item
    if (vec.size != 0) {
        printf("FAIL: Vector size mismatch after pop. Expected 0, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }
    
    printf("PASS: Item popped from vector successfully!\n");
    vectorDestroy(&vec);
    
    return 0;
}

u8 testResize() {
    Vector vec;
    u8 status;
    u8 oldCap = VECTOR_MIN_CAPACITY;

    printf("Test 7/%d: Resize vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    // Push items to trigger a resize
    for (int i = 0; i < 10; i++) {
        int *item = malloc(sizeof(int));
        *item = i;
        status = vectorPush(&vec, item);
        if (oldCap != vec.capacity) {
            printf("Vector resized successfully to capacity %zu after pushing %d items.\n", vec.capacity, i + 1);
            oldCap = vec.capacity; // Update oldSize to the new capacity
        }
        if (status != VECTOR_SUCCESS) {
            printf("FAIL: Failed to push item %d to vector: status code %d\n", i, status);
            vectorDestroy(&vec);
            return 1;
        }
    }

    if (vec.size != 10) {
        printf("FAIL: Vector size mismatch after resizing. Expected 10, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }


    // Test pop
    for (int i = 9; i >= 0; i--) {
        int *poppedItem = vectorPop(&vec);
        if (poppedItem == NULL || *poppedItem != i) {
            printf("FAIL: Popped item mismatch. Expected %d, got %d\n", i, poppedItem ? *poppedItem : -1);
            free(poppedItem); // Free the popped item if it was allocated
            vectorDestroy(&vec);
            return 1;
        }
        free(poppedItem); // Free the popped item
        if (oldCap != vec.capacity) {
            printf("Vector resized successfully to capacity %zu after popping item %d.\n", vec.capacity, i);
            oldCap = vec.capacity; // Update oldSize to the new capacity
        }

        if (vec.capacity < VECTOR_MIN_CAPACITY) {
            printf("FAIL: Vector capacity should not be less than %d after popping.\n", VECTOR_MIN_CAPACITY);
            vectorDestroy(&vec);
            return 1;
        }
    }
    
    printf("PASS: Vector resized successfully!\n");
    vectorDestroy(&vec);
    
    return 0;
}

u8 testGet() {
    Vector vec;
    u8 status;
    int *retrievedItem;

    printf("Test 8/%d: Get item from vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    retrievedItem = (int *)vectorGet(&vec, 0);
    if (retrievedItem != NULL) {
        printf("FAIL: Expected NULL for empty vector, got %d\n", *retrievedItem);
        vectorDestroy(&vec);
        return 1;
    }

    // Push an item to get it later
    int *item = malloc(sizeof(int));
    *item = 42;
    status = vectorPush(&vec, item);
    
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to push item to vector: status code %d\n", status);
        vectorDestroy(&vec);
        return 1;
    }

    retrievedItem = (int *)vectorGet(&vec, 0);
    if (retrievedItem == NULL || *retrievedItem != 42) {
        printf("FAIL: Retrieved item mismatch. Expected 42, got %d\n", retrievedItem ? *retrievedItem : -1);
        free(retrievedItem); // Free the retrieved item if it was allocated
        vectorDestroy(&vec);
        return 1;
    }
    
    if (vec.size != 1) {
        printf("FAIL: Vector size mismatch after get. Expected 1, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }

    retrievedItem = (int *)vectorGet(&vec, 11);
    if (retrievedItem != NULL) {
        printf("FAIL: Expected NULL for out-of-bounds index, got %d\n", *retrievedItem);
        vectorDestroy(&vec);
        return 1;
    }
    
    printf("PASS: Item retrieved from vector successfully!\n");
    vectorDestroy(&vec);
    
    return 0;
}

u8 testDelete() {
    Vector vec;
    u8 status;
    int *deletedItem;

    printf("Test 9/%d: Delete item from vector.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    // Push items to delete later
    for (int i = 0; i < 5; i++) {
        int *item = malloc(sizeof(int));
        *item = i;
        status = vectorPush(&vec, item);
        if (status != VECTOR_SUCCESS) {
            printf("FAIL: Failed to push item %d to vector: status code %d\n", i, status);
            vectorDestroy(&vec);
            return 1;
        }
    }

    deletedItem = (int *)vectorDelete(&vec, 2);
    if (deletedItem == NULL || *deletedItem != 2) {
        printf("FAIL: Deleted item mismatch. Expected 2, got %d\n", deletedItem ? *deletedItem : -1);
        free(deletedItem); // Free the deleted item if it was allocated
        vectorDestroy(&vec);
        return 1;
    }
    
    free(deletedItem); // Free the deleted item
    if (vec.size != 4) {
        printf("FAIL: Vector size mismatch after delete. Expected 4, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }

    deletedItem = (int *)vectorGet(&vec, 2);
    if (deletedItem == NULL || *deletedItem != 3) {
        printf("FAIL: Retrieved item mismatch after delete. Expected 3, got %d\n", deletedItem ? *deletedItem : -1);
        free(deletedItem); // Free the retrieved item if it was allocated
        vectorDestroy(&vec);
        return 1;
    }
    
    printf("PASS: Item deleted from vector successfully!\n");
    vectorDestroy(&vec);
    
    return 0;
}

int main(int argc, char** argv) {
    printf("Running vector tests...\n");
    if (testUninitializedVector()) return 1; else passedTests++;
    if (testInit()) return 1; else passedTests++;
    if (testNullPointerInit()) return 1; else passedTests++;
    if (testEmptyVectorDestroy()) return 1; else passedTests++;
    if (testPushItem()) return 1; else passedTests++;
    if (testPop()) return 1; else passedTests++;
    if (testResize()) return 1; else passedTests++;
    if (testGet()) return 1; else passedTests++;
    if (testDelete()) return 1; else passedTests++;
    
    printf("All tests completed.\n");
    printf("Tests passed: %d/%d; Percent passed: %d%\n", passedTests, totalTests, (passedTests * 100) / totalTests);
    return 0;
}
