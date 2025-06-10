#ifndef DATA_H
#define DATA_H

#include "../src/engine/engine.h"

u8 dataValidateLine(const char *line, u32 lineNum);
u8 dataExtractKeyValue(const char *line, DataTuple keyValue);


#endif // DATA_H