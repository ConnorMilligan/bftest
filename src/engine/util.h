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

// Vector
#define VECTOR_INIT_CAPACITY 4

typedef struct {
    void **items;
    usize size;
    usize capacity;
    u8 initialized;
} Vector;

u8 vectorInit(Vector *vec);
u8 vectorPush(Vector *vec, void *item);
void *vectorPop(Vector *vec);
void *vectorGet(Vector *vec, usize index);
u8 vectorDelete(Vector *vec, usize index);
u8 vectorDestroy(Vector *vec);

#endif // UTIL_H
