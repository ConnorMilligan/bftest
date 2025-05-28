#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stddef.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

// Unsigned int types.
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Regular int types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floating point types
typedef float f32;
typedef double f64;

// Size
typedef size_t usize;

// Undefine the data type aliases.
#undef uint8_t
#undef uint16_t
#undef uint32_t
#undef uint64_t
#undef int8_t
#undef int16_t
#undef int32_t
#undef int64_t

// List
typedef struct Node {
    void  *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    unsigned int size;
} List;

void listInit(List *list);
u8 listDestroy(List *list);
u8 listPush(List *list, void *data);
u8 listDelete(List *list, usize index);
Node* listPop(List *list);
Node* listGet(List *list, usize index);


#endif // UTIL_H
