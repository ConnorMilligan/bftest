#ifndef ENGINE_H
#define ENGINE_H

#include "errors.h"
#include "util.h"

#include <raylib.h>

// Defines
#define WINDOW_TITLE "Hokkaido Map"
#define BASE_WIDTH 640
#define BASE_HEIGHT 480

#define FONT_SIZE_BASE 16
#define TEXTURE_BASE_SIZE 1
#define DATA_BUF_LEN 16
#define MAX_TEXTURES 16

// Enums
enum GameState {
    MAIN_MENU,
    GAME,
};

// // Structs
typedef struct {
    Font font;
    Font fontJP;
    u8 fontSize;
    f32 textureScale;
    u8 menuSel;

    Vector subprefectures;
    
    Texture2D textures[MAX_TEXTURES];

    enum GameState gameState;
} Context;

// Data
typedef struct {
    char name[DATA_BUF_LEN];
    char namejp[DATA_BUF_LEN];
    char population[DATA_BUF_LEN];
    char area[DATA_BUF_LEN];
    char capital[DATA_BUF_LEN];
    char capitaljp[DATA_BUF_LEN];
    u8 atlasIndex;
} Subprefecture;

// // ENGINE
// Context
u8 contextBuild(Context *ctx);
u8 contextCleanup(Context *ctx);

// Data
u8 dataInit(Context *ctx);

// Game
u8 gameInit(Context *ctx);
void gameRender(Context *ctx);
void gameInput(Context *ctx);
u8 gameCleanup(Context *ctx);

// // RENDERING
// Screen
void screenDrawMainMenu(Context *ctx);
void screenDrawGame(Context *ctx);
u8 screenProcessResize(Context *ctx);

// Menu
void menuDrawBorder(Context *ctx);
void menuDrawSPrefSel(Context *ctx);
void menuDrawSPrefInfo(Context *ctx);

// Text
u16 textGetRows(u8 fontSize);
u16 textGetCols(u8 fontSize);

void textDrawString(Context *ctx, const char *str, u16 x, u16 y, Color color);
void textDrawStringJP(Context *ctx, const char *str, u16 x, u16 y, Color color);



#endif // CONTEXT_H
