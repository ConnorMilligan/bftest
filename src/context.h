#ifndef CONTEXT_H
#define CONTEXT_H

#include <raylib.h>

typedef struct {
    Font font;
} Context;

int contextBuild(Context *ctx);
int contextCleanup(Context *ctx);

#endif // CONTEXT_H