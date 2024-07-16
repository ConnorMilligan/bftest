#include "game.h"
#include "util.h"

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

    float scale = MIN((float)GetScreenWidth()/BASE_WIDTH, (float)GetScreenHeight()/BASE_HEIGHT);

    BeginDrawing();

    ClearBackground(BLACK);
    SetTextLineSpacing(24*scale);
    //DrawRectangle(20, 20, BASE_WIDTH-40-((float)BASE_WIDTH*scale), BASE_HEIGHT-40-((float)BASE_HEIGHT*scale), WHITE);
    //DrawRectangle(25, 25, BASE_WIDTH-50-((float)BASE_WIDTH*scale), BASE_HEIGHT-50-((float)BASE_HEIGHT*scale), BLACK);

    // Draw borders
    for (int i = 24*scale; i < GetScreenWidth()-(24*scale); i+=24*scale) {
        DrawTextEx(ctx->font, "═", (Vector2){i*scale, 0}, 24*scale, 0, WHITE);
        DrawTextEx(ctx->font, "═", (Vector2){i*scale, (BASE_HEIGHT-24)*scale}, 24*scale, 0, WHITE);
    }
    for (int i = 24*scale; i < GetScreenHeight()-(24*scale); i+=24*scale) {
        DrawTextEx(ctx->font, "║", (Vector2){0, i*scale}, 24*scale, 0, WHITE);
        DrawTextEx(ctx->font, "║", (Vector2){(BASE_WIDTH-24)*scale, i*scale}, 24*scale, 0, WHITE);
    }
    DrawTextEx(ctx->font, "╚", (Vector2){0, (BASE_HEIGHT-24)*scale}, 24*scale, 0, WHITE);
    DrawTextEx(ctx->font, "╝", (Vector2){(BASE_WIDTH-24)*scale, (BASE_HEIGHT-24)*scale}, 24*scale, 0, WHITE);
    DrawTextEx(ctx->font, "╔", (Vector2){0, 0}, 24*scale, 0, WHITE);
    DrawTextEx(ctx->font, "╗", (Vector2){(BASE_WIDTH-24)*scale, 0}, 24*scale, 0, WHITE);

    
    DrawTextEx(ctx->font, "╔═╦═╗\n│", (Vector2){1200*scale, 40*scale}, 24*scale, 0, WHITE);
    DrawTextEx(ctx->font, cp437, (Vector2){40*scale, 120*scale}, 24*scale, 0, WHITE);
    DrawTextEx(ctx->font, "Hello world, this is a test", (Vector2){40, 40}, 24*scale, 0, WHITE);

    EndDrawing();
}