#ifndef GAME_H
#define GAME_H

#include "context.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

void gameRender(Context *ctx);

#endif // GAME_H