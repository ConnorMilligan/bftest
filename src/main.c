#include <raylib.h>
#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;
    u8 status;

    status = gameInit(&ctx);

    switch (status) {
        case GAME_FONT_MISSING:
            printf("ERROR: Fonts were unable to be found; aborting.\n");
            gameCleanup(&ctx);
            return 1;
            break;

        case GAME_RES_MISSING:
            printf("ERROR: Could not locate the resources directory; aborting.\n");
            return 1;
            break;
            
        default:
            printf("Game initialization successful.\n");
            break;
    }


    while (!WindowShouldClose()) {
        gameRender(&ctx);
    }

    gameCleanup(&ctx);

    return 0;
}
