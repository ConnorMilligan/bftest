#ifndef DATA_H
#define DATA_H

#include "../src/engine/engine.h"
#include "../src/engine/util.h"

#define BUFFER_SIZE 256
#define MAX_DATA_FIELDS 32

enum DataTypes {
    DATA_TYPE_NONE,
    DATA_TYPE_SUBREGION
};

typedef char DataTuple[2][BUFFER_SIZE];

u8 dataValidateLine(const char *line, u32 lineNum);
u8 dataExtractKeyValue(const char *line, DataTuple keyValue);
u8 dataLoadFile(const char *filename, char **data);
u8 dataPopulateVector(Vector *vec, const char *data);
u8 dataLoadStructureFromTuples(Vector *vec, enum DataTypes type, DataTuple fields[MAX_DATA_FIELDS]);



#endif // DATA_H