// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

static i8 passedTests = 0;
static const u8 totalTests = 2;

u8 testLineValidation() {
    u8 status;

    const char *validLine = "[key:value]";
    const char *invalidLine1 = "key:value"; // Missing brackets
    const char *invalidLine2 = "[key:value"; // Missing closing bracket
    const char *invalidLine3 = "[keyvalue]"; // Missing colon
    const char *invalidLine4 = "[keyvalue]:"; 
    const char *invalidLine5 = "]key:value]";

    printf("Test 1/%d: Validate lines.\n", totalTests);
    status = dataValidateLine(validLine, 1);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Valid line failed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(invalidLine1, 2);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Invalid line 1 passed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(invalidLine2, 3);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Invalid line 2 passed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(invalidLine3, 4);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Invalid line 3 passed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(invalidLine4, 5);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Invalid line 4 passed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(invalidLine5, 6);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Invalid line 5 passed validation: status code %d\n", status);
        return 1;
    }

    printf("PASS: All line validations passed successfully!\n");
    return 0;
}

u8 dataTestKeyValueExtraction() {
    DataTuple keyValue;
    const char *line = "[key:value]";
    const char *lineUni = "[NAME_JP:空知]";

    u8 status = dataExtractKeyValue(line, keyValue);

    if (status != DATA_SUCCESS) {
        printf("FAIL: Key-value extraction failed: status code %d\n", status);
        return 1;
    }
    if (strcmp(keyValue[0], "key") != 0 || strcmp(keyValue[1], "value") != 0) {
        printf("FAIL: Extracted key-value does not match expected values.\n");
        return 1;
    }
    printf("PASS: Key-value extraction successful: key='%s', value='%s'\n", keyValue[0], keyValue[1]);

    status = dataExtractKeyValue(lineUni, keyValue);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Key-value extraction for Japanese line failed: status code %d\n", status);
        return 1;
    }
    if (strcmp(keyValue[0], "NAME_JP") != 0 || strcmp(keyValue[1], "空知") != 0) {
        printf("FAIL: Extracted key-value does not match expected values for Japanese line.\n");
        return 1;
    }
    printf("PASS: Key-value extraction for Japanese line successful: key='%s', value='%s'\n", keyValue[0], keyValue[1]);

    return 0;
}

int main(int argc, char** argv) {
    printf("Running context tests...\n");
    if (testLineValidation()) return 1; else passedTests++;
    if (dataTestKeyValueExtraction()) return 1; else passedTests++;

    printf("All tests completed.\n");
    printf("Tests passed: %d/%d; Percent passed: %d%\n", passedTests, totalTests, (passedTests * 100) / totalTests);


    Context ctx;

    contextBuild(&ctx);


    contextCleanup(&ctx);

    return 0;
}