#include "engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TEST_BUILD
#define INTERNAL
#else
#define INTERNAL static
#endif

INTERNAL u8 dataValidate(const char *data) {
    char buffer[256];
    u32 count = 0;
    u32 lineCount = 0;

    if (data == NULL || strlen(data) == 0) {
        fprintf(stderr, "ERROR: Data is NULL or empty.\n");
        return DATA_DIR_EMPTY;
    }

    while (data[count] != '\0') {
        if (data[count] == '\n') {
            lineCount++;
            if (lineCount > 1000) { // Arbitrary limit to prevent excessive lines
                fprintf(stderr, "ERROR: Too many lines in data file.\n");
                return DATA_INVALID_FORMAT;
            }
        }
        count++;

        if (count >= 256) {
            fprintf(stderr, "ERROR: Data exceeds maximum buffer size.\n");
            return DATA_INVALID_FORMAT;
        }

        // Copy the data to a buffer for further processing if needed
        buffer[count - 1] = data[count - 1];

        //print line with line number
        if (data[count - 1] == '\n') {
            buffer[count - 1] = '\0'; // Null-terminate the line
            printf("Line %u: %s\n", lineCount, buffer);
            memset(buffer, 0, sizeof(buffer)); // Clear the buffer for the next line
        }
    }

    return DATA_SUCCESS;
}

INTERNAL char *dataLoadFile(const char *filename) {
    char *data = LoadFileText(filename);

    if (data == NULL) {
        fprintf(stderr, "ERROR: Could not load file: %s\n", filename);
        return NULL;
    }

    // Validate the loaded data
    u8 validationStatus = dataValidate(data);
    if (validationStatus != DATA_SUCCESS) {
        fprintf(stderr, "ERROR: Data validation failed with status code %d.\n", validationStatus);
        free(data); // Free the data if validation fails
        return NULL;
    }

    return data;
}

u8 dataInit(Context *ctx) {
    if (ctx == NULL) {
        fprintf(stderr, "ERROR: Context is NULL.\n");
        return DATA_DIR_EMPTY;
    }

    char *data = dataLoadFile("tests/res/test.txt");

    if (data == NULL) {
        fprintf(stderr, "ERROR: Failed to load data file.\n");
        return DATA_FILE_NOT_FOUND;
    }

    free(data); // Free the loaded data after use


    return 0;
}