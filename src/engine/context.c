#include "engine.h"

#include <raylib.h>
#include <stdio.h>

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

static u8 contextLoadTextures(Context *ctx) {
    u8 status;
    Texture2D texture;
    FilePathList textureFiles;

    textureFiles = LoadDirectoryFiles("res/textures");

    if (textureFiles.count == 0) {
        // No textures found
        return TEXTURE_FILE_NOT_FOUND;
    }

    for (int i = 0; i < textureFiles.count; i++) {
        // Load each texture and add it to the vector
        texture = LoadTexture(textureFiles.paths[i]);
        if (texture.id == 0) {
            // Failed to load texture
            UnloadDirectoryFiles(textureFiles);
            return TEXTURE_FILE_NOT_FOUND;
        }

        status = vectorPush(&ctx->textures, &texture);
        if (status != VECTOR_SUCCESS) {
            UnloadTexture(texture);
            UnloadDirectoryFiles(textureFiles);
            return CONTEXT_VECTOR_INIT_FAILED;
        }
    }

    printf("INFO: Loaded %d textures from directory.\n", textureFiles.count);

    UnloadDirectoryFiles(textureFiles); // Unload the directory files after loading textures

    return TEXTURE_SUCCESS;
}

u8 contextBuild(Context *ctx) {
    u8 status;

    ctx->font = (Font){};
    ctx->fontJP = (Font){};
    ctx->fontSize = FONT_SIZE_BASE;
    ctx->gameState = GAME;

    // Load fonts if not in test mode
#ifndef TEST_BUILD
    contextLoadFonts(ctx);
    if (!FileExists("res/fonts/mxplus/MxPlus_IBM_BIOS.ttf") || !FileExists("res/fonts/bestten/BestTen-DOT.otf"))
        return CONTEXT_FONT_MISSING;
#endif
    status = vectorInit(&ctx->subprefectures);
    if (status != VECTOR_SUCCESS) {
        return CONTEXT_VECTOR_INIT_FAILED;
    }

    status = vectorInit(&ctx->textures);
    if (status != VECTOR_SUCCESS) {
        return CONTEXT_VECTOR_INIT_FAILED;
    }
    
    status = dataInit(ctx);
    if (status != DATA_SUCCESS) {
        return CONTEXT_DATA_INIT_FAILED;
    }

    // Load textures
    status = contextLoadTextures(ctx);
    if (status != TEXTURE_SUCCESS) {
        return status; // Return the error code from texture loading
    }

    printf("INFO: Context built successfully.\n");
    for (int i = 0; i < ctx->textures.size; i++) {
        Texture2D *texture = vectorGet(&ctx->textures, i);
        printf("INFO: Loaded texture %d with ID %u\n", i, texture->id);
    }

    return CONTEXT_SUCCESS;
}

u8 contextCleanup(Context *ctx) {
    u8 status;
    // Unload fonts if not in test mode
#ifndef TEST_BUILD
    UnloadFont(ctx->font);
    UnloadFont(ctx->fontJP);
#endif

    // Cleanup the vectors
    status = vectorDestroy(&ctx->subprefectures);
    if (status != VECTOR_SUCCESS) {
        return VECTOR_DESTROY_FAILED;
    }

    // Unload all textures
    for (int i = 0; i < ctx->textures.size; i++) {
        Texture2D *texture = vectorGet(&ctx->textures, i);
        UnloadTexture(*texture);
    }

    return CONTEXT_SUCCESS;
}
