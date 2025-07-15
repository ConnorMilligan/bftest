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

        case CONTEXT_DATA_INIT_FAILED:
            printf("ERROR: Data initialization failed; aborting.\n");
            gameCleanup(&ctx);
            return 1;
            break;

        case CONTEXT_VECTOR_INIT_FAILED:
            printf("ERROR: Vector initialization failed; aborting.\n");
            gameCleanup(&ctx);
            return 1;
            break;
            
        default:
            printf("Game initialization successful.\n");
            break;
    }


    while (!WindowShouldClose()) {
        gameRender(&ctx);
        gameInput(&ctx);
        
        // close the window if the user presses escape
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    status = gameCleanup(&ctx);
    if (status != CONTEXT_SUCCESS) {
        printf("ERROR: Game cleanup failed with status code %d.\n", status);
        return 1;
    }
    printf("INFO: Game cleanup successful.\n");

    return 0;
}
