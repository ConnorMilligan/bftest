#ifndef CONTEXT_H
#define CONTEXT_H

#include <raylib.h>

#include "util.h"

enum GameState {
    MAIN_MENU,
    GAME,
};

typedef struct {
    Font font;
    u8 fontSize;
    enum GameState gameState;
} Context;

u8 contextBuild(Context *ctx);
u8 contextCleanup(Context *ctx);

#endif // CONTEXT_H