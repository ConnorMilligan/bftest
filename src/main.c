#include <raylib.h>
#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;

    gameInit(&ctx);

    Texture2D hokkaido = LoadTexture("../res/hokkaido3.png");
    while (!WindowShouldClose()) {
        gameRender(&ctx);
        //DrawTextureEx(hokkaido, (Vector2) {200, 100}, 0, 4, WHITE);
        DrawTextureEx(hokkaido, (Vector2) {200, 100}, 0, 2, WHITE);
    }
    UnloadTexture(hokkaido);

    contextCleanup(&ctx);

    return 0;
}
