#include "engine.h"

#include <stdio.h>
#include <raylib.h>

static void testRender(Context *ctx);

u8 gameInit(Context *ctx) {
    printf("Starting initialization proceedure.\n");

    if (!DirectoryExists("res/")) {
        return GAME_RES_MISSING;
    }

    printf("Initializing window.\n");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
   
    // Initialize the window
    InitWindow(BASE_WIDTH, BASE_HEIGHT, WINDOW_TITLE);

    //HideCursor();
    SetWindowMinSize(320, 240);
    SetTargetFPS(60);

    printf("Building context.\n");
    return contextBuild(ctx);
}


void gameRender(Context *ctx) {
    // Reset scaling if screen size changes
    if (IsWindowResized()) {
        screenProcessResize(ctx);
    }

    BeginDrawing();

    switch (ctx->gameState) {
        case MAIN_MENU:
            screenDrawMainMenu(ctx);
            break;
        case GAME:
            screenDrawGame(ctx);
            break;
        
        default:
            break;
    }

    EndDrawing();
}

void gameInput(Context *ctx) {
    switch (ctx->gameState) {
        case GAME:
            if (IsKeyPressed(KEY_UP)) {
                ctx->menuSel = (ctx->menuSel > 0) ? ctx->menuSel - 1 : ctx->subprefectures.size - 1;
            } else if (IsKeyPressed(KEY_DOWN)) {
                ctx->menuSel = (ctx->menuSel < ctx->subprefectures.size - 1) ? ctx->menuSel + 1 : 0;
            } 
    }
}

u8 gameCleanup(Context *ctx) {
    CloseWindow();
    return contextCleanup(ctx);
}

static void testRender(Context *ctx) {
    const char *cp437 = 
    " ☺☻♥♦♣♠•◘○◙♂♀♪♫☼\n"
    "►◄↕‼¶§▬↨↑↓→←∟↔▲▼\n"
    " !\"#$%&'()*+,-./\n"
    "0123456789:;<=>?\n"
    "@ABCDEFGHIJKLMNO\n"
    "PQRSTUVWXYZ[\\]^_\n"
    "`abcdefghijklmno\n"
    "pqrstuvwxyz{|}~\x7F\n"
    "ÇüéâäàåçêëèïîìÄÅ\n"
    "ÉæÆôöòûùÿÖÜ¢£¥₧ƒ\n"
    "áíóúñÑªº¿⌐¬½¼¡«»\n"
    "░▒▓│┤╡╢╖╕╣║╗╝╜╛┐\n"
    "└┴┬├─┼╞╟╚╔╩╦╠═╬╧\n"
    "╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀\n"
    "αßΓπΣσµτΦΘΩδ∞φε∩\n"
    "≡±≥≤⌠⌡÷≈°∙·√ⁿ²■\xA0";

    
    ClearBackground(BLACK);
    SetTextLineSpacing(0);
    //DrawRectangle(20, 20, BASE_WIDTH-40-((float)BASE_WIDTH*scale), BASE_HEIGHT-40-((float)BASE_HEIGHT*scale), WHITE);
    //DrawRectangle(25, 25, BASE_WIDTH-50-((float)BASE_WIDTH*scale), BASE_HEIGHT-50-((float)BASE_HEIGHT*scale), BLACK);

    menuDrawBorder(ctx);


    textDrawString(ctx, "Hello world, this is a test.", 1, 1, WHITE);
    textDrawStringJP(ctx, "あいうえお、札幌市、北海道", 1, 2, WHITE);
    textDrawString(ctx, cp437, 1, 4, WHITE);
    textDrawString(ctx, "╔═╦═╗\n│", 25, 5, RED);
    char fps[5];
    snprintf(fps, 5, "%d", GetFPS());
    textDrawString(ctx, fps, textGetRows(ctx->fontSize)-3, 1, YELLOW);
}


