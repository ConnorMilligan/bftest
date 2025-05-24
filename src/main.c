#include <raylib.h>
#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;
    u8 status;

    status = gameInit(&ctx);

    if (status != 0) {
        printf("The window was not able to initialize properly; aborting. Error code: %d\n", status);
        return status;
    }

    while (!WindowShouldClose()) {
        gameRender(&ctx);
    }

    contextCleanup(&ctx);

    return 0;
}
