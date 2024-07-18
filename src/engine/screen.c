#include "menu.h"
#include "screen.h"
#include "text.h"

void screenDrawMainMenu(Context *ctx) {
    // Draw outline
    menuDrawBorder(ctx);
    textDrawString(ctx, "Main Menu", 2, 2, WHITE);
}