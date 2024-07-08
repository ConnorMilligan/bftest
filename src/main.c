#include <raylib.h>
#include <stdio.h>

#include "font.h"

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


int main(int argc, char **argv) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Hello world!");
    // Define an array of codepoints you want to load
    int codepointsCount = 0;
    int *codepoints = LoadCodepoints(cp437, &codepointsCount);

    // Load the font with the specified codepoints
    Font font = LoadFontEx("../res/MxPlus_IBM_BIOS.ttf", 32, codepoints, codepointsCount);

    // Unload the codepoints array
    UnloadCodepoints(codepoints);
    SetTextLineSpacing(40);


    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(20, 20, screenWidth-40, screenHeight-40, WHITE);
        DrawRectangle(25, 25, screenWidth-50, screenHeight-50, BLACK);
        DrawTextEx(font, cp437, (Vector2){40, 40}, 40, 5, WHITE);
        DrawTextEx(font, "╔═╦═╗\n│", (Vector2){1200, 40}, 40, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    ExportFontAsCode(font, "font.h");
    UnloadFont(font);

    return 0;
}