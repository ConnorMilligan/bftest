// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/engine/util.h"

#define ASSERT(x) do { if (!(x)) { fprintf(stderr, "ASSERT FAILED: %s\n", #x); exit(1); } } while(0)

int test_listPush() {
    List list;
    listInit(&list);
    int value = 42;
    ASSERT(listPush(&list, &value) == 0);
    ASSERT(list.size == 1);
    listDestroy(&list);
    return 0;
}

int test_listPop() {
    List list;
    listInit(&list);
    int value = 99;
    listPush(&list, &value);
    Node* n = listPop(&list);
    ASSERT(n != NULL);
    ASSERT(*(int*)n->data == 99);
    listDestroy(&list);
    return 0;
}

int test_listDelete() {
    List list;
    listInit(&list);
    int a = 1, b = 2, c = 3;
    listPush(&list, &a); // index 2 (tail)
    listPush(&list, &b); // index 1
    listPush(&list, &c); // index 0 (head)

    ASSERT(list.size == 3);
    ASSERT(listDelete(&list, 1) == 0);  // deletes node with data b (2)
    ASSERT(list.size == 2);
    ASSERT(*(int*)listGet(&list, 0)->data == 3); // c
    ASSERT(*(int*)listGet(&list, 1)->data == 1); // a

    listDestroy(&list);
    return 0;
}

int test_listGet_invalid() {
    List list;
    listInit(&list);
    int x = 5;
    listPush(&list, &x);

    ASSERT(listGet(&list, 1) == NULL);  // only index 0 is valid
    ASSERT(listGet(&list, 100) == NULL);
    ASSERT(listGet(&list, -1) == NULL);  // if your index is usize (unsigned), this may not compile

    listDestroy(&list);
    return 0;
}

int test_listPop_empty() {
    List list;
    listInit(&list);
    ASSERT(listPop(&list) == NULL);
    listDestroy(&list);
    return 0;
}

int test_listMultiplePushPop() {
    List list;
    listInit(&list);

    int a = 10, b = 20, c = 30;
    listPush(&list, &a);
    listPush(&list, &b);
    listPush(&list, &c);

    ASSERT(list.size == 3);

    Node* n1 = listPop(&list);
    ASSERT(n1 != NULL);
    ASSERT(*(int*)n1->data == 30);  // LIFO order

    Node* n2 = listPop(&list);
    ASSERT(n2 != NULL);
    ASSERT(*(int*)n2->data == 20);

    Node* n3 = listPop(&list);
    ASSERT(n3 != NULL);
    ASSERT(*(int*)n3->data == 10);

    Node* n4 = listPop(&list);
    ASSERT(n4 == NULL);  // now empty

    listDestroy(&list);
    return 0;
}

int test_listDelete_invalid() {
    List list;
    listInit(&list);
    int val = 100;
    listPush(&list, &val);

    ASSERT(listDelete(&list, 1) != 0); // only index 0 is valid
    ASSERT(listDelete(&list, 999) != 0);
    ASSERT(list.size == 1);

    listDestroy(&list);
    return 0;
}

int test_listDestroy_twice() {
    List list;
    listInit(&list);
    int val = 5;
    listPush(&list, &val);

    listDestroy(&list);
    // Call again just to make sure it doesn't double-free
    listDestroy(&list);

    return 0;
}

int test_listPush_null() {
    List list;
    listInit(&list);

    ASSERT(listPush(&list, NULL) == 0);
    ASSERT(list.size == 1);

    Node* n = listPop(&list);
    ASSERT(n != NULL);
    ASSERT(n->data == NULL);

    listDestroy(&list);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <test_name>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "listPush") == 0) return test_listPush();
    if (strcmp(argv[1], "listPop") == 0) return test_listPop();
    if (strcmp(argv[1], "listDelete") == 0) return test_listDelete();
    if (strcmp(argv[1], "listGet_invalid") == 0) return test_listGet_invalid();
    if (strcmp(argv[1], "listPop_empty") == 0) return test_listPop_empty();
    if (strcmp(argv[1], "listMultiplePushPop") == 0) return test_listMultiplePushPop();
    if (strcmp(argv[1], "listDelete_invalid") == 0) return test_listDelete_invalid();
    if (strcmp(argv[1], "listDestroy_twice") == 0) return test_listDestroy_twice();
    if (strcmp(argv[1], "listPush_null") == 0) return test_listPush_null();

    fprintf(stderr, "Unknown test: %s\n", argv[1]);
    return 1;
}
