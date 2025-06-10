#ifndef ENGINE_H
#define ENGINE_H

#include "errors.h"
#include "util.h"

#include <raylib.h>

// Defines
#define WINDOW_TITLE "bftest"
#define BASE_WIDTH 640
#define BASE_HEIGHT 480

#define FONT_SIZE_BASE 16
#define DATA_BUF_LEN 16

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

    enum GameState gameState;
} Context;

// Data

typedef char DataTuple[2][DATA_BUF_LEN];

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
u8 gameCleanup(Context *ctx);

// // RENDERING
// Screen
void screenDrawMainMenu(Context *ctx);
u8 screenProcessResize(Context *ctx);

// Menu
void menuDrawBorder(Context *ctx);

// Text
u16 textGetRows(u8 fontSize);
u16 textGetCols(u8 fontSize);

void textDrawString(Context *ctx, const char *str, u16 x, u16 y, Color color);
void textDrawStringJP(Context *ctx, const char *str, u16 x, u16 y, Color color);



#endif // CONTEXT_H
