#include "engine.h"

#include <raylib.h>

static void contextLoadFonts(Context *ctx) {
    Font fontJP, cp437Font;
    i32 *codepoints, codepointsCount;

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


    codepointsCount = 0;
    codepoints = LoadCodepoints(cp437, &codepointsCount);

    // Load the font with the specified codepoints
    cp437Font = LoadFontEx("res/fonts/mxplus/MxPlus_IBM_BIOS.ttf", 32, codepoints, codepointsCount);
    UnloadCodepoints(codepoints); // Unload the codepoints array after loading the font

    // Same for JP font
    codepointsCount = 0;
    codepoints = LoadCodepoints(jp, &codepointsCount);

    fontJP = LoadFontEx("res/fonts/bestten/BestTen-DOT.otf", 32, codepoints, codepointsCount);

    UnloadCodepoints(codepoints);

    // Set the loaded fonts to the context
    ctx->font = cp437Font;
    ctx->fontJP = fontJP;
}

u8 contextBuild(Context *ctx) {
    ctx->font = (Font){};
    ctx->fontJP = (Font){};
    ctx->fontSize = FONT_SIZE_BASE;
    ctx->gameState = GAME;

    // Load fonts if not in test mode
    #ifndef TEST_MAIN
    contextLoadFonts(ctx);
    if (!FileExists("res/fonts/mxplus/MxPlus_IBM_BIOS.ttf") || !FileExists("res/fonts/bestten/BestTen-DOT.otf"))
        return CONTEXT_FONT_MISSING;
    #endif

    dataInit(ctx);

    return CONTEXT_SUCCESS;
}

u8 contextCleanup(Context *ctx) {
    // Unload fonts if not in test mode
    #ifndef TEST_MAIN
    UnloadFont(ctx->font);
    UnloadFont(ctx->fontJP);
    #endif

    return CONTEXT_SUCCESS;
}
