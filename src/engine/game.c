#include "game.h"
#include "menu.h"
#include "screen.h"
#include "text.h"
#include "util.h"

void testRender(Context *ctx);

void gameRender(Context *ctx) {
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

    f32 scale = MIN((float)GetScreenWidth()/BASE_WIDTH, (float)GetScreenHeight()/BASE_HEIGHT);
    ctx->fontSize = 24*scale;



    ClearBackground(BLACK);
    SetTextLineSpacing(24*scale);
    //DrawRectangle(20, 20, BASE_WIDTH-40-((float)BASE_WIDTH*scale), BASE_HEIGHT-40-((float)BASE_HEIGHT*scale), WHITE);
    //DrawRectangle(25, 25, BASE_WIDTH-50-((float)BASE_WIDTH*scale), BASE_HEIGHT-50-((float)BASE_HEIGHT*scale), BLACK);

    menuDrawBorder(ctx);

    textDrawString(ctx, "Hello world, this is a test", 1, 1, WHITE);
    textDrawString(ctx, cp437, 1, 3, WHITE);
    textDrawString(ctx, "╔═╦═╗\n│", 25, 5, RED);
}