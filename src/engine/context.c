#include "engine.h"

#include <raylib.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>


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
        "あ≡±≥≤⌠⌡÷≈°∙·√ⁿ²■ō\xA0";
    
    const char *jp = 
        "あいうえおかきくけこ"
        "さしすせそたちつてと"
        "なにぬねのはひふへほ"
        "はひふへほまみむめも"
        "らりるれろやゆよわを"
        "ん、札幌市北海道オホ"
        "ーツク函館十勝内室蘭"
        "帯広宗谷江差旭川札幌"
        "知空石狩日高浦河渡島"
        "檜山留萌稚網走釧路根"
        "室倶安岩見沢後志上";


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
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "MSP_([0-9]+)_.+\\.png";

    // Track which texture indices have been filled
    bool filled[MAX_TEXTURES] = {false};
    bool extraTextureLoaded = false;

    textureFiles = LoadDirectoryFiles("res/textures");

    if (textureFiles.count == 0) {
        return TEXTURE_FILE_NOT_FOUND;
    }

    // Compile regex
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return TEXTURE_FILE_NOT_FOUND;
    }

    for (int f = 0; f < textureFiles.count; f++) {
        const char *filename = GetFileName(textureFiles.paths[f]);

        if (regexec(&regex, filename, 2, matches, 0) == 0) {
            // Extract index from match
            int start = matches[1].rm_so;
            int end = matches[1].rm_eo;
            char indexStr[8];
            snprintf(indexStr, end - start + 1, "%.*s", end - start, filename + start);
            int index = atoi(indexStr);

            if (index >= 0 && index < MAX_TEXTURES) {
                texture = LoadTexture(textureFiles.paths[f]);
                if (texture.id == 0) {
                    regfree(&regex);
                    UnloadDirectoryFiles(textureFiles);
                    return TEXTURE_FILE_NOT_FOUND;
                }
                ctx->textures[index] = texture;
                filled[index] = true;
            }
        } else {
            // Non-matching filename → load to final slot
            if (!extraTextureLoaded) {
                texture = LoadTexture(textureFiles.paths[f]);
                if (texture.id == 0) {
                    regfree(&regex);
                    UnloadDirectoryFiles(textureFiles);
                    return TEXTURE_FILE_NOT_FOUND;
                }
                ctx->textures[MAX_TEXTURES - 1] = texture;
                filled[MAX_TEXTURES - 1] = true;
                extraTextureLoaded = true;
            }
        }
    }

    regfree(&regex);
    UnloadDirectoryFiles(textureFiles);

    // Load default for any unfilled slots
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (!filled[i]) {
            texture = LoadTexture("res/MP_hokkaido.png");
            if (texture.id == 0) {
                return TEXTURE_FILE_NOT_FOUND;
            }
            ctx->textures[i] = texture;
        }
    }


    return TEXTURE_SUCCESS;
}

u8 contextBuild(Context *ctx) {
    u8 status;

    ctx->font = (Font){};
    ctx->fontJP = (Font){};
    ctx->fontSize = FONT_SIZE_BASE;
    ctx->textureScale = TEXTURE_BASE_SIZE;
    ctx->gameState = GAME;
    ctx->menuSel = 0;

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
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (ctx->textures[i].id != 0) {
            UnloadTexture(ctx->textures[i]);
        }
    }


    return CONTEXT_SUCCESS;
}
