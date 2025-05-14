#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;

    contextBuild(&ctx);

    while (!WindowShouldClose()) {
        gameRender(&ctx);
    }

    contextCleanup(&ctx);

    return 0;
}