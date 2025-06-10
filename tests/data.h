#ifndef DATA_H
#define DATA_H

#include "../src/engine/engine.h"

u8 dataValidateLine(const char *line, u32 lineNum);
u8 dataExtractKeyValue(const char *line, DataTuple keyValue);
u8 dataLoadFile(const char *filename, char **data);
u8 dataPopulateVector(Vector *vec, const char *data);


#endif // DATA_H