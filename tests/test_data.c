// tests/test_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

static i8 passedTests = 0;
static const u8 totalTests = 5;

u8 testLineValidation() {
    u8 status;

    const char *validLine1 = "[key:value]";
    const char *validLine2 = ""; // Empty line
    const char *invalidLine1 = "key:value"; // Missing brackets
    const char *invalidLine2 = "[key:value"; // Missing closing bracket
    const char *invalidLine3 = "[keyvalue]"; // Missing colon
    const char *invalidLine4 = "[keyvalue]:"; 
    const char *invalidLine5 = "]key:value]";

    printf("Test 1/%d: Validate lines.\n", totalTests);
    status = dataValidateLine(validLine1, 1);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Valid line failed validation: status code %d\n", status);
        return 1;
    }

    status = dataValidateLine(validLine2, 1);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Empty line failed validation: status code %d\n", status);
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

u8 testKeyValueExtraction() {
    DataTuple keyValue;
    const char *line = "[key:value]";
    const char *lineUni = "[NAME_JP:空知]";

    u8 status = dataExtractKeyValue(line, keyValue);

    printf("Test 2/%d: Extract key-value pairs from line.\n", totalTests);

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

u8 testLoadFile() {
    u8 status;
    const char *correct = "tests/res/test.txt";
    const char *incorrect = "tests/res/nonexistent.txt";
    const char *extra_data = "tests/res/test_extra_data.txt";
    char *data = NULL;

    status = dataLoadFile(correct, &data);

    printf("Test 3/%d: Load file '%s'.\n", totalTests, correct);

    if (status != DATA_SUCCESS) {
        printf("FAIL: Failed to load file '%s'.\n", correct);
        return 1;
    }
    printf("PASS: File '%s' loaded successfully.\n", correct);

    if (data == NULL || strlen(data) == 0) {
        printf("FAIL: Loaded data is NULL or empty.\n");
        return 1;
    }
    free(data);

    status = dataLoadFile(incorrect, &data);
    if (status != DATA_FILE_NOT_FOUND) {
        printf("FAIL: Expected DATA_FILE_NOT_FOUND for non-existent file, got status code %d\n", status);
        free(data);
        return 1;
    }
    printf("PASS: Non-existent file correctly returned DATA_FILE_NOT_FOUND.\n");
    if (data != NULL) {
        printf("FAIL: Data should be NULL for non-existent file.\n");
        free(data);
        return 1;
    }


    free(data);
    return 0;
}

u8 testPopulateVector() {
    Vector vec;
    u8 status;
    char *data;
    
    dataLoadFile("tests/res/test.txt", &data);

    printf("Test 4/%d: Populate vector with data.\n", totalTests);
    status = vectorInit(&vec);
    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        free(data);
        return 1;
    }

    status = dataPopulateVector(&vec, data);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Failed to populate vector with data: status code %d\n", status);
        vectorDestroy(&vec);
        free(data);
        return 1;
    }

    if (vec.size == 0) {
        printf("FAIL: Vector size is zero after population.\n");
        vectorDestroy(&vec);
        free(data);
        return 1;
    }

    printf("PASS: Vector populated successfully with %zu items.\n", vec.size);

    vectorDestroy(&vec);
    free(data);
    
    return 0;
}

u8 testLoadStructureFromTuples() {
    Vector vec;
    u8 status;
    DataTuple fields[MAX_DATA_FIELDS] = {
        {"NAME_EN", "TestSubprefecture"},
        {"NAME_JP", "テストサブプレフェクチャ"},
        {"POPULATION", "1000000"},
        {"AREA", "500.5"},
        {"CAPITAL_EN", "TestCapital"},
        {"CAPITAL_JP", "テストキャピタル"},
        {"ATLAS_INDEX", "1"}
    };

    DataTuple missingFields[MAX_DATA_FIELDS] = {
        {"NAME_EN", "TestSubprefecture"},
        {"NAME_JP", "テストサブプレフェクチャ"},
        {"POPULATION", "1000000"},
        {"AREA", "500.5"},
        // Missing CAPITAL and CAPITAL_JP
        {"ATLAS_INDEX", "1"}
    };

    printf("Test 5/%d: Load structure from tuples.\n", totalTests);
    status = vectorInit(&vec);

    if (status != VECTOR_SUCCESS) {
        printf("FAIL: Failed to initialize vector: status code %d\n", status);
        return 1;
    }

    status = dataLoadStructureFromTuples(&vec, DATA_TYPE_SUBREGION, fields);
    if (status != DATA_SUCCESS) {
        printf("FAIL: Failed to load structure from tuples: status code %d\n", status);
        vectorDestroy(&vec);
        return 1;
    }

    if (vec.size != 1) {
        printf("FAIL: Vector size mismatch after loading structure. Expected 1, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }

    Subprefecture *subregion = (Subprefecture *)vectorGet(&vec, 0);
    if (subregion == NULL) {
        printf("FAIL: Loaded subregion is NULL.\n");
        vectorDestroy(&vec);
        return 1;
    }

    if (strcmp(subregion->name, "TestSubprefecture") != 0 ||
        strcmp(subregion->namejp, "テストサブプレフェクチャ") != 0 ||
        strcmp(subregion->population, "1000000") != 0 ||
        strcmp(subregion->area, "500.5") != 0 ||
        strcmp(subregion->capital, "TestCapital") != 0 ||
        strcmp(subregion->capitaljp, "テストキャピタル") != 0 ||
        subregion->atlasIndex != 1) {
        printf("FAIL: Loaded subregion fields do not match expected values.\n");
        printf("Expected: NAME_EN=%s, NAME_JP=%s, POPULATION=%s, AREA=%s, CAPITAL_EN=%s, CAPITAL_JP=%s, ATLAS_INDEX=%d\n",
               "TestSubprefecture", "テストサブプレフェクチャ", "1000000", "500.5", "TestCapital", "テストキャピタル", 1);
        vectorDestroy(&vec);
        return 1;
    }

    status = dataLoadStructureFromTuples(&vec, DATA_TYPE_SUBREGION, missingFields);
    if (status != DATA_INVALID_FORMAT) {
        printf("FAIL: Expected DATA_INVALID_FORMAT for missing fields, got status code %d\n", status);
        vectorDestroy(&vec);
        return 1;
    }

    printf("PASS: Structure loaded successfully with all required fields.\n");
    if (vec.size != 1) {
        printf("FAIL: Vector size mismatch after loading structure with missing fields. Expected 1, got %zu\n", vec.size);
        vectorDestroy(&vec);
        return 1;
    }

    subregion = (Subprefecture *)vectorGet(&vec, 0);
    if (subregion == NULL) {
        printf("FAIL: Loaded subregion is NULL after loading with missing fields.\n");
        vectorDestroy(&vec);
        return 1;
    }

    printf("PASS: Structure loaded successfully from tuples.\n");
    vectorDestroy(&vec);

    return 0;
}


int main(int argc, char** argv) {
    printf("Running context tests...\n");
    if (testLineValidation()) return 1; else passedTests++;
    if (testKeyValueExtraction()) return 1; else passedTests++;
    if (testLoadFile()) return 1; else passedTests++;
    if (testPopulateVector()) return 1; else passedTests++;
    //if (testLoadStructureFromTuples()) return 1; else passedTests++;

    printf("All tests completed.\n");
    printf("Tests passed: %d/%d; Percent passed: %d%\n", passedTests, totalTests, (passedTests * 100) / totalTests);



    return 0;
}