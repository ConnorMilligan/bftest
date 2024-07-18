#include <raylib.h>
#include <stdio.h>

#include "engine/context.h"
#include "engine/game.h"

int main(int argc, char **argv) {
    Context ctx;

    contextBuild(&ctx);

    while (!WindowShouldClose()) {
        gameRender(&ctx);
    }

    contextCleanup(&ctx);

    return 0;
}