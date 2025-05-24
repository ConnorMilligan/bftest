#ifndef ENGINE_H
#define ENGINE_H

#include "util.h"

#include <raylib.h>

// Defines
#define WINDOW_TITLE "bftest"
#define BASE_WIDTH 640
#define BASE_HEIGHT 480

#define FONT_SIZE_BASE 16

// Enums
enum GameState {
    MAIN_MENU,
    GAME,
};

// Structs
typedef struct {
    Font font;
    Font fontJP;
    u8 fontSize;

    enum GameState gameState;
} Context;

// // ENGINE
// Context
u8 contextBuild(Context *ctx);
u8 contextCleanup(Context *ctx);

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
