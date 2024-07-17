#ifndef CONTEXT_H
#define CONTEXT_H

#include <raylib.h>

#include "util.h"

typedef struct {
    Font font;
    u8 fontSize;
} Context;

u8 contextBuild(Context *ctx);
u8 contextCleanup(Context *ctx);

#endif // CONTEXT_H