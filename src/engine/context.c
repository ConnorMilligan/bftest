#include "engine.h"

#include <raylib.h>

u8 contextBuild(Context *ctx) {
    Font fontJP, cp437Font;
    u32 *codepoints, codepointsCount;

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
        "あ≡±≥≤⌠⌡÷≈°∙·√ⁿ²■\xA0";
    
    const char *jp = 
        "あいうえおかきくけこ"
        "さしすせそたちつてと"
        "なにぬねのはひふへほ"
        "はひふへほまみむめも"
        "らりるれろやゆよわを"
        "ん、札幌市北海道";

    // -------------------------------
    // | Font loading
    // -------------------------------


    // Define an array of codepoints to load
    codepointsCount = 0;
    codepoints = LoadCodepoints(cp437, &codepointsCount);

    // Load the font with the specified codepoints
    cp437Font = LoadFontEx("res/fonts/mxplus/MxPlus_IBM_BIOS.ttf", 32, codepoints, codepointsCount);

    // Same for JP font
    codepointsCount = 0;
    codepoints = LoadCodepoints(jp, &codepointsCount);

    fontJP = LoadFontEx("res/fonts/bestten/BestTen-DOT.otf", 32, codepoints, codepointsCount);


    // Unload the codepoints array
    UnloadCodepoints(codepoints);

    // -------------------------------
    // | Set the context fields
    // -------------------------------

    ctx->font = cp437Font;
    ctx->fontJP = fontJP;
    ctx->fontSize = FONT_SIZE_BASE;
    ctx->gameState = GAME;

    if (!FileExists("res/fonts/mxplus/MxPlus_IBM_BIOS.ttf") || !FileExists("res/fonts/bestten/BestTen-DOT.otf"))
        return CONTEXT_FONT_MISSING;

    dataInit(ctx);

    return CONTEXT_SUCCESS;
}

u8 contextCleanup(Context *ctx) {
    UnloadFont(ctx->font);
    UnloadFont(ctx->fontJP);

    return CONTEXT_SUCCESS;
}
