#ifndef TEXT_H
#define TEXT_H


#include <raylib.h>

#include "context.h"
#include "util.h"

u16 textGetRows(u8 fontSize);
u16 textGetCols(u8 fontSize);

void textDrawString(Context *ctx, const char *str, u16 x, u16 y, Color color);

#endif // TEXT_H