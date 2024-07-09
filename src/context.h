#ifndef CONTEXT_H
#define CONTEXT_H

#include <raylib.h>

#define WINDOW_TITLE "bftest"
#define BASE_WIDTH 1920
#define BASE_HEIGHT 1080

typedef struct {
    Font font;
} Context;

int contextBuild(Context *ctx);
int contextCleanup(Context *ctx);

#endif // CONTEXT_H