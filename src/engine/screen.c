#include "engine.h"

#include <stdio.h>

void screenDrawMainMenu(Context *ctx) {
    // Draw outline
    menuDrawBorder(ctx);
    textDrawString(ctx, "Main Menu", 2, 2, WHITE);
}

u8 screenProcessResize(Context *ctx) {
    f32 scale = MIN((float)GetScreenWidth()/BASE_WIDTH, (float)GetScreenHeight()/BASE_HEIGHT);
    ctx->fontSize = FONT_SIZE_BASE*scale;

    ctx->textureScale = scale;

    return 0;
}

void screenDrawGame(Context *ctx) {    
    ClearBackground(BLACK);
    SetTextLineSpacing(0);

    menuDrawBorder(ctx);
    menuDrawSPrefSel(ctx);
    menuDrawSPrefInfo(ctx);

    // Draw the game content
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (ctx->textures[i].id != 0)
            DrawTextureEx(ctx->textures[i], (Vector2) {(GetScreenWidth()/2)-(100*2.4*ctx->textureScale), 10}, 0, 2.4*ctx->textureScale, WHITE);
    }

    char fps[5];
    snprintf(fps, 5, "%d", GetFPS());
    textDrawString(ctx, fps, textGetRows(ctx->fontSize)-3, 1, YELLOW);
}