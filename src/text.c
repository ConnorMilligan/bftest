#include "text.h"
#include <math.h>

u16 textGetRows(u8 fontSize) {
    return floor(GetScreenWidth() / fontSize);
}

u16 textGetCols(u8 fontSize) {
    return floor(GetScreenHeight() / fontSize);
}

void textDrawString(Context *ctx, const char *str, u16 x, u16 y, Color color) {
    // Draw string
    DrawTextEx(ctx->font, str, (Vector2){x*ctx->fontSize, y*ctx->fontSize}, ctx->fontSize, 0, color);
}