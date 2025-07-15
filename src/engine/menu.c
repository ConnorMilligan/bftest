#include "engine.h"

void menuDrawBorder(Context *ctx) {
    // Draw borders
    for (u8 i = 1; i < textGetRows(ctx->fontSize)-1; i++) {
        textDrawString(ctx, "═", i, 0, WHITE);
        if (i == 27) continue; // Skip the input menu horizontal line
        textDrawString(ctx, "═", i, textGetCols(ctx->fontSize)-1, WHITE);
    }

    for (u8 i = 1; i < textGetCols(ctx->fontSize)-1; i++) {
        if (i != 20) textDrawString(ctx, "║", 0, i, WHITE);
        if (i == 13) continue; // Skip the input menu vertical line
        textDrawString(ctx, "║", textGetRows(ctx->fontSize)-1, i, WHITE);
    }

    textDrawString(ctx, "╔", 0, 0, WHITE);
    textDrawString(ctx, "╗", textGetRows(ctx->fontSize)-1, 0, WHITE);
    textDrawString(ctx, "╚", 0, textGetCols(ctx->fontSize)-1, WHITE);
    textDrawString(ctx, "╝", textGetRows(ctx->fontSize)-1, textGetCols(ctx->fontSize)-1, WHITE);

    // Input menu corners
    for (u8 i = 28; i < textGetRows(ctx->fontSize)-1; i++) {
        textDrawString(ctx, "═", i, 13, WHITE);
    }
    for (u8 i = 14; i < textGetCols(ctx->fontSize)-1; i++) {
        if (i == 20) continue; // Skip the input menu vertical line
        textDrawString(ctx, "║", 27, i, WHITE);
    }

    textDrawString(ctx, "╔", 27, 13, WHITE);
    textDrawString(ctx, "╣", textGetRows(ctx->fontSize)-1, 13, WHITE);
    textDrawString(ctx, "╩", 27, textGetCols(ctx->fontSize)-1, WHITE);


}

void menuDrawSPrefSel(Context *ctx) {
    u8 x = 29, y = 15;

    for (int i = 0; i < ctx->subprefectures.size; i++) {
        Subprefecture *subpref = vectorGet(&ctx->subprefectures, i);
        if (subpref == NULL) continue; // Skip if subprefecture is NULL

        // Draw the subprefecture name
        

        if (i == ctx->menuSel) {
            textDrawString(ctx, subpref->name, x, y + i, YELLOW);
        } else {
            textDrawString(ctx, subpref->name, x, y + i, WHITE);
        }
    }
}

void menuDrawSPrefInfo(Context *ctx) {
    u8 x = 2, y = 22;
    Subprefecture *subpref = vectorGet(&ctx->subprefectures, ctx->menuSel);

    for (u8 i = 1; i < 27; i++) {
        textDrawString(ctx, "═", i, 20, WHITE);
    }
    textDrawString(ctx, "╣", 27, 20, WHITE);
    textDrawString(ctx, "╟", 0, 20, WHITE);

    if (subpref == NULL) return; // Skip if subprefecture is NULL

    // Draw the subprefecture information
    textDrawString(ctx, "Name: ", x, y, WHITE);
    textDrawString(ctx, subpref->name, x + 6, y, WHITE);
    textDrawString(ctx, "Name (JP): ", x, y + 1, WHITE);
    textDrawStringJP(ctx, subpref->namejp, x + 12, y + 1, WHITE);
    textDrawString(ctx, "Population: ", x, y + 2, WHITE);
    textDrawString(ctx, subpref->population, x + 12, y + 2, WHITE);
    textDrawString(ctx, "Area: ", x, y + 3, WHITE);
    textDrawString(ctx, subpref->area, x + 6, y + 3, WHITE);
    textDrawString(ctx, "Capital: ", x, y + 4, WHITE);
    textDrawString(ctx, subpref->capital, x + 10, y + 4, WHITE);
    textDrawString(ctx, "Capital (JP): ", x, y + 5, WHITE);
    textDrawStringJP(ctx, subpref->capitaljp, x + 16, y + 5, WHITE);
    
}