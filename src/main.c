#include <raylib.h>
#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;

    if (u8 status = gameInit(&ctx); status != 0) {
        printf("The window was not able to initialize properly; aborting. Error code: %d\n", status);
        return status;
    }

    Texture2D hokkaido = LoadTexture("res/hokkaido.png");
    while (!WindowShouldClose()) {
        gameRender(&ctx);
        //DrawTextureEx(hokkaido, (Vector2) {200, 100}, 0, 4, WHITE);
        DrawTextureEx(hokkaido, (Vector2) {200, 100}, 0, 2, WHITE);
    }
    UnloadTexture(hokkaido);

    contextCleanup(&ctx);

    return 0;
}
