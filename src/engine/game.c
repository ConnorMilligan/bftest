#include "engine.h"

#include <stdio.h>
#include <raylib.h>

void testRender(Context *ctx);

u8 gameInit(Context *ctx) {
    printf("Starting initialization proceedure.\n");

    if (!DirectoryExists("res/")) {
        printf("Could not locate the resources directory (res/). Please make sure the res directory is in the same location as the executable.\n");
        return 2;
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
            testRender(ctx);
            break;
        
        default:
            break;
    }

    EndDrawing();
}

u8 gameCleanup(Context *ctx) {
    CloseWindow();
    return contextCleanup(ctx);
}

void testRender(Context *ctx) {
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
