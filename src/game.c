#include "game.h"

void gameRender(Context *ctx) {
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

    BeginDrawing();

    ClearBackground(BLACK);
    DrawRectangle(20, 20, BASE_WIDTH-40, BASE_HEIGHT-40, WHITE);
    DrawRectangle(25, 25, BASE_WIDTH-50, BASE_HEIGHT-50, BLACK);
    SetTextLineSpacing(24);
    DrawTextEx(ctx->font, "╔═╦═╗\n│", (Vector2){1200, 40}, 24, 0, WHITE);
    DrawTextEx(ctx->font, cp437, (Vector2){40, 120}, 24, 0, WHITE);
    DrawTextEx(ctx->font, "Hello world, this is a test", (Vector2){40, 40}, 24, 0, WHITE);

    EndDrawing();
}