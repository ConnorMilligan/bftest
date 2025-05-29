// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>

#include "../src/engine/engine.h"

int main(int argc, char** argv) {
    Context ctx;

    contextBuild(&ctx);


    contextCleanup(&ctx);

    return 0;
}