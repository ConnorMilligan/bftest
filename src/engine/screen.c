#include "engine.h"

void screenDrawMainMenu(Context *ctx) {
    // Draw outline
    menuDrawBorder(ctx);
    textDrawString(ctx, "Main Menu", 2, 2, WHITE);
}

u8 screenProcessResize(Context *ctx) {
    f32 scale = MIN((float)GetScreenWidth()/BASE_WIDTH, (float)GetScreenHeight()/BASE_HEIGHT);
    ctx->fontSize = FONT_SIZE_BASE*scale;
    return 0;
}
