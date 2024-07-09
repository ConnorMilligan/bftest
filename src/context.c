#include "context.h"

int contextBuild(Context *ctx) {
    // Characterset of to define the codepoints to load
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


    // Initialize the window
    InitWindow(BASE_WIDTH, BASE_HEIGHT, WINDOW_TITLE);
    // Set the font to the context
    SetTargetFPS(60);

    // -------------------------------
    // | Font loading
    // -------------------------------

    // Define an array of codepoints you want to load
    int codepointsCount = 0;
    int *codepoints = LoadCodepoints(cp437, &codepointsCount);

    // Load the font with the specified codepoints
    Font cp437Font = LoadFontEx("../res/MxPlus_IBM_BIOS.ttf", 32, codepoints, codepointsCount);

    // Unload the codepoints array
    UnloadCodepoints(codepoints);

    // -------------------------------
    // | Set the context fields
    // -------------------------------

    ctx->font = cp437Font;

    return 0;
}

int contextCleanup(Context *ctx) {
    CloseWindow();
    UnloadFont(ctx->font);

    return 0;
}