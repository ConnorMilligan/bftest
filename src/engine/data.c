#include "engine.h"

#include <stdio.h>

u8 dataInit(Context *ctx) {
    // View files
    FilePathList files = LoadDirectoryFiles("res/data");

    printf("FIles capacity: %d, files count %d\n", files.capacity, files.capacity);

    for (int i = 0; i < files.count; i++) {
        printf("Path: %s\n", files.paths[i]);
    }

    UnloadDirectoryFiles(files);

    return 0;
}