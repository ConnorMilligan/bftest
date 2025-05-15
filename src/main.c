#include <raylib.h>
#include <stdio.h>

#include "engine/engine.h"

int main(int argc, char **argv) {
    Context ctx;

    gameInit(&ctx);

    Texture2D hokkaido = LoadTexture("../res/hokkaido.png");
    while (!WindowShouldClose()) {
        gameRender(&ctx);
        DrawTextureEx(hokkaido, (Vector2) {300, 150}, 0, 4, BLUE);
    }
    UnloadTexture(hokkaido);

    contextCleanup(&ctx);

    return 0;
}
