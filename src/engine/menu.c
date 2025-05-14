#include "engine.h"

void menuDrawBorder(Context *ctx) {
    // Draw borders
    for (u8 i = 1; i < textGetRows(ctx->fontSize)-1; i++) {
        textDrawString(ctx, "═", i, 0, WHITE);
        textDrawString(ctx, "═", i, textGetCols(ctx->fontSize)-1, WHITE);
    }

    for (u8 i = 1; i < textGetCols(ctx->fontSize)-1; i++) {
        textDrawString(ctx, "║", 0, i, WHITE);
        textDrawString(ctx, "║", textGetRows(ctx->fontSize)-1, i, WHITE);
    }

    textDrawString(ctx, "╔", 0, 0, WHITE);
    textDrawString(ctx, "╗", textGetRows(ctx->fontSize)-1, 0, WHITE);
    textDrawString(ctx, "╚", 0, textGetCols(ctx->fontSize)-1, WHITE);
    textDrawString(ctx, "╝", textGetRows(ctx->fontSize)-1, textGetCols(ctx->fontSize)-1, WHITE);
}