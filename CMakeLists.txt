cmake_minimum_required(VERSION 3.14)
project(bftest)

# Set normal compiler flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated -Wall")

# Set versions of dependencies
set(RAYLIB_VERSION 5.5)

# Include FetchContent
include(FetchContent)

message(STATUS "Using Raylib version ${RAYLIB_VERSION}")

# Fetch Raylib
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib)

# Set the project files
file(GLOB_RECURSE PROJECT_HEADERS "src/*.h")
file(GLOB_RECURSE PROJECT_SOURCES "src/*.c")

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Link Raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Copy the res/ folder to the same directory as the built executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

# Enable testing
enable_testing()

# Build test executable
add_executable(test_list tests/test_list.c src/engine/list.c)
target_include_directories(test_list PRIVATE ${CMAKE_SOURCE_DIR}/src/engine)

# Register each logical test separately
add_test(NAME test_listPush COMMAND test_list listPush)
add_test(NAME test_listPop  COMMAND test_list listPop)
add_test(NAME test_listDelete      COMMAND test_list listDelete)
add_test(NAME test_listGet_invalid COMMAND test_list listGet_invalid)
add_test(NAME test_listPop_empty   COMMAND test_list listPop_empty)
add_test(NAME test_listMultiplePushPop COMMAND test_list listMultiplePushPop)
add_test(NAME test_listDelete_invalid  COMMAND test_list listDelete_invalid)
add_test(NAME test_listDestroy_twice   COMMAND test_list listDestroy_twice)
add_test(NAME test_listPush_null       COMMAND test_list listPush_null)

