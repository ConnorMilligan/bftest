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

void menuDrawSPSel(Context *ctx) {
    
    for (int i = 0; i < ctx->subprefectures.size; i++) {
        Subprefecture *subpref = vectorGet(&ctx->subprefectures, i);
        if (subpref == NULL) continue; // Skip if subprefecture is NULL

        // Draw the subprefecture name
        

        if (i == ctx->menuSel) {
            textDrawString(ctx, subpref->name, 28, 2 + i, YELLOW);
        } else {
            textDrawString(ctx, subpref->name, 28, 2 + i, WHITE);
        }
    }
}