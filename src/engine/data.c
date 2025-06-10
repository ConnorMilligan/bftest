#include "engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

#ifdef TEST_BUILD
#define INTERNAL
#else
#define INTERNAL static
#endif

INTERNAL u8 dataValidateLine(const char *line, u32 lineNum) {
    if (line == NULL || strlen(line) == 0) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Line %d is NULL or empty.\n", lineNum);
#endif
        return DATA_DIR_EMPTY;
    }

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
    u32 lineNum = 0;

    if (data == NULL || strlen(data) == 0) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Data is NULL or empty.\n");
#endif
        return DATA_DIR_EMPTY;
    }

    while (data[count] != '\0') {
        if (data[count] == '\n') {
            buffer[lineCount] = '\0'; // Null-terminate the buffer

            printf("INFO: Line %d: %s\n", lineNum, buffer);
            memset(buffer, 0, sizeof(buffer));

            lineCount = 0;
            lineNum++;
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

INTERNAL char *dataLoadFile(const char *filename) {
    char *data = LoadFileText(filename);

    if (data == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Could not load file: %s\n", filename);
#endif
        return NULL;
    }

    // Validate the loaded data
    u8 validationStatus = dataValidate(data);
    if (validationStatus != DATA_SUCCESS) {
        free(data); // Free the data if validation fails
        return NULL;
    }

    return data;
}

u8 dataInit(Context *ctx) {
    if (ctx == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Context is NULL.\n");
#endif
        return DATA_DIR_EMPTY;
    }

    char *data = dataLoadFile("tests/res/test.txt");

    if (data == NULL) {
#ifdef TEST_BUILD
        fprintf(stderr, "ERROR: Failed to load data file.\n");
#endif
        return DATA_FILE_NOT_FOUND;
    }

    free(data); // Free the loaded data after use


    return 0;
}