#include "engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define MAX_DATA_FIELDS 32

#ifdef TEST_BUILD
#define INTERNAL
#else
#define INTERNAL static
#endif

typedef char DataTuple[2][BUFFER_SIZE];

enum DataTypes {
    DATA_TYPE_NONE,
    DATA_TYPE_SUBREGION
};

static const char *dataTypeNames[] = {
    "",
    "SUBREGION"
};

static const char* dataFields[][MAX_DATA_FIELDS] = {
    {},
    {
        "NAME_EN",
        "NAME_JP",
        "POPULATION",
        "AREA",
        "CAPITAL_EN",
        "CAPITAL_JP",
        "ATLAS_INDEX"
    }
};

INTERNAL u8 dataValidateLine(const char *line, u32 lineNum) {
    if (line == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Line %d is NULL.\n", lineNum);
#endif
        return DATA_DIR_EMPTY;
    }

    if (strlen(line) == 0)
        return DATA_SUCCESS; // Empty line is considered valid

    const char *openBracket = strchr(line, '[');
    const char *closeBracket = strrchr(line, ']');
    const char *colon = strchr(line, ':');

    if (colon == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Line %d is missing a colon.\n", lineNum);
#endif
        return DATA_INVALID_FORMAT;
    }
    if (openBracket == NULL || closeBracket == NULL || openBracket > closeBracket) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Line %d is missing brackets or has them in the wrong order.\n", lineNum);
#endif
        return DATA_INVALID_FORMAT;
    }

    if (colon < openBracket || colon > closeBracket) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Line %d has a colon outside of brackets.\n", lineNum);
#endif
        return DATA_INVALID_FORMAT;
    }

    return DATA_SUCCESS;
}

INTERNAL u8 dataValidate(const char *data) {
    char buffer[BUFFER_SIZE];
    u32 count = 0;
    u32 lineCount = 0;
    u32 lineNum = 1;
    u8 status;

    if (data == NULL || strlen(data) == 0) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Data is NULL or empty.\n");
#endif
        return DATA_DIR_EMPTY;
    }

    while (data[count] != '\0') {
        if (data[count] == '\n') {
            buffer[lineCount] = '\0'; // Null-terminate the buffer

            //printf("INFO: Line %d: %s\n", lineNum, buffer);
            memset(buffer, 0, sizeof(buffer));
            status = dataValidateLine(buffer, lineNum);

            if (status != DATA_SUCCESS) {
#ifdef TEST_BUILD
                fprintf(stderr, "ERROR: Line %d validation failed with status code %d.\n", lineNum, status);
#endif
                return status;
            }
            
            lineCount = 0;
            lineNum++;
            count++;
            continue;
        }

        buffer[lineCount] = data[count];
        if (lineCount >= BUFFER_SIZE - 1) {
#ifdef TEST_BUILD
            fprintf(stderr, "ERROR: Line %d exceeds buffer size of %d characters.\n", lineNum, BUFFER_SIZE - 1);
#endif
            return DATA_LINE_TOO_LONG;
        }

        lineCount++;
        count++;
    }

    return DATA_SUCCESS;
}

INTERNAL u8 dataExtractKeyValue(const char *line, DataTuple keyValue) {
    if (line == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: NULL pointer passed to dataExtractKeyValue.\n");
#endif
        return DATA_LINE_EMPTY;
    }

    const char *openBracket = strchr(line, '[');
    const char *closeBracket = strrchr(line, ']');
    const char *colon = strchr(line, ':');

    size_t keyLength = colon - openBracket - 1;
    size_t valueLength = closeBracket - colon - 1;


    strncpy(keyValue[0], openBracket + 1, keyLength);
    keyValue[0][keyLength] = '\0'; // Null-terminate the key

    strncpy(keyValue[1], colon + 1, valueLength);
    keyValue[1][valueLength] = '\0'; // Null-terminate the value
    return DATA_SUCCESS;
}

INTERNAL u8 dataLoadFile(const char *filename, char **data) {
    *data = LoadFileText(filename);


    if (*data == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Could not load file: %s\n", filename);
#endif
        return DATA_FILE_NOT_FOUND;
    }

    // Validate the loaded data
    u8 validationStatus = dataValidate(*data);
    if (validationStatus != DATA_SUCCESS) {
        free(*data); // Free the data if validation fails
        return validationStatus;
    }

    return DATA_SUCCESS;
}

u8 dataLoadStructureFromTuples(Vector *vec, enum DataTypes type, DataTuple fields[MAX_DATA_FIELDS]) {
    void *data = NULL;
    
    if (vec == NULL || fields == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Vector or fields is NULL.\n");
#endif
        return DATA_INVALID_FORMAT;
    }

    if (type == DATA_TYPE_NONE) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Data type is not set.\n");
#endif
        return DATA_INVALID_FORMAT;
    }

    if (type == DATA_TYPE_SUBREGION) {

        // check all required fields are present
        for (usize i = 0; i < MAX_DATA_FIELDS; i++) {
            if (fields[i][0][0] == 0) {
                break; // Stop checking if we hit an empty field
            }
            if (strcmp(fields[i][0], dataFields[DATA_TYPE_SUBREGION][i]) != 0) {
#ifdef TEST_BUILD
                fprintf(stderr, "ERROR: Missing required field '%s' for subregion.\n", dataFields[DATA_TYPE_SUBREGION][i]);
#endif
                return DATA_INVALID_FORMAT;
            }

#ifdef TEST_BUILD
            printf("INFO: Field %zu: %s = %s\n", i, fields[i][0], fields[i][1]);
#endif
        }

        // Create a new subregion structure
        data = malloc(sizeof(Subprefecture));
        if (data == NULL) {
#ifdef TEST_BUILD
            fprintf(stderr, "ERROR: Memory allocation failed for subregion.\n");
#endif
            return DATA_ALLOCATION_FAILED;
        }

    }
    // Add the data to the vector
    u8 status = vectorPush(vec, data);
    if (status != VECTOR_SUCCESS) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Failed to push data to vector: status code %d.\n", status);
#endif
        free(data); // Free if push fails
        return status;
    }

    // Reset the fields
    for (usize i = 0; i < MAX_DATA_FIELDS; i++) {
        memset(fields[i][0], 0, BUFFER_SIZE);
        memset(fields[i][1], 0, BUFFER_SIZE);
    }

    return DATA_SUCCESS;
}

u8 dataPopulateVector(Vector *vec, const char *data) {
    if (vec == NULL || data == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Vector or data is NULL.\n");
#endif
        return DATA_INVALID_FORMAT;
    }
    char buffer[BUFFER_SIZE];
    usize count = 0;
    u32 lineCount = 0;
    u32 lineNum = 1;
    u8 status = 0;
    enum DataTypes dataType = DATA_TYPE_NONE;
    DataTuple keyValue;
    DataTuple fields[MAX_DATA_FIELDS];

    memset(fields, 0, sizeof(fields));

    if (data == NULL || strlen(data) == 0) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Data is NULL or empty.\n");
#endif
        return DATA_DIR_EMPTY;
    }

    while (data[count] != '\0') {
        char current = data[count];

        if (current == '\n' || current == '\r') {
            buffer[lineCount] = '\0';

            //printf("INFO: Line %d: %s\n", lineNum, buffer);

            if (strlen(buffer) == 0 || buffer[0] == '\n' || buffer[0] == '\r') {
                //printf("EMPTY: Line %d is empty, skipping.\n", lineNum);
                memset(buffer, 0, sizeof(buffer));

                count++;
                lineCount = 0;
                lineNum++;
                continue; // Skip empty lines
            }

            status = dataExtractKeyValue(buffer, keyValue);
            if (status != DATA_SUCCESS) {
#ifdef TEST_BUILD
                fprintf(stderr, "ERROR: Line %d extraction failed with status code %d.\n", lineNum, status);
#endif
                return status;
            }

            // Determine data type
            if (strcmp(keyValue[0], "DATA") == 0) {
                if (strcmp(keyValue[1], "SUBREGION") == 0) {
                    if (dataType != DATA_TYPE_NONE) {
#ifdef TEST_BUILD
                        fprintf(stderr, "ERROR: Data type already set to %s, cannot set to %s again.\n", dataTypeNames[dataType], keyValue[1]);
#endif
                        return DATA_INVALID_FORMAT;
                    }
                    dataType = DATA_TYPE_SUBREGION;
#ifdef TEST_BUILD
                    printf("INFO: Data type set to %s.\n", dataTypeNames[dataType]);
#endif
                }
            }

            // Load in subregion
            else if (dataType == DATA_TYPE_SUBREGION) {

               
                if (strcmp(keyValue[0], "SUBREGION") == 0) {
#ifdef TEST_BUILD 
                    printf("INFO: Loading subregion %s.\n", keyValue[1]);
#endif
                }

                else if (strcmp(keyValue[0], "NAME_EN") == 0) {
                    strncpy(fields[0][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[0][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "NAME_JP") == 0) {
                    strncpy(fields[1][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[1][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "POPULATION") == 0) {
                    strncpy(fields[2][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[2][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "AREA") == 0) {
                    strncpy(fields[3][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[3][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "CAPITAL_EN") == 0) {
                    strncpy(fields[4][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[4][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "CAPITAL_JP") == 0) {
                    strncpy(fields[5][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[5][1], keyValue[1], BUFFER_SIZE);
                } else if (strcmp(keyValue[0], "ATLAS_INDEX") == 0) {
                    strncpy(fields[6][0], keyValue[0], BUFFER_SIZE);
                    strncpy(fields[6][1], keyValue[1], BUFFER_SIZE);

                    // final data loaded
                    status = dataLoadStructureFromTuples(vec, dataType, fields);
                    if (status != DATA_SUCCESS) {
#ifdef TEST_BUILD
                        fprintf(stderr, "ERROR: Failed to load data structure from tuples: status code %d.\n", status);
#endif
                        return status;
                    }

                } else {
#ifdef TEST_BUILD
                    fprintf(stderr, "ERROR: Unknown field '%s' in line %d.\n", keyValue[0], lineNum);
#endif
                    return DATA_INVALID_FORMAT;
                }
            }

            memset(buffer, 0, BUFFER_SIZE);
            lineCount = 0;
            lineNum++;
            count++;
            continue;
        }

        buffer[lineCount] = data[count];

        lineCount++;
        count++;
    }

    return DATA_SUCCESS;
}

u8 dataInit(Context *ctx) {
    if (ctx == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Context is NULL.\n");
#endif
        return DATA_DIR_EMPTY;
    }
    u8 status;
    char *data = NULL;
    
    status = dataLoadFile("res/data/subprefectures.txt", &data);


    if (status != DATA_SUCCESS) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Failed to load data file.\n");
#endif
        return DATA_FILE_NOT_FOUND;
    }

    status = dataPopulateVector(&ctx->subprefectures, data);
    free(data); // Free the data after populating the vector
    if (status != DATA_SUCCESS) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Failed to populate vector with data: status code %d.\n", status);
#endif
        return status;
    }

    printf("INFO: Data initialized successfully with %zu subprefectures.\n", ctx->subprefectures.size);
    return DATA_SUCCESS;
}