#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef bool b8;

#define V2_FMT "<%.3f, %.3f>"
#define V3_FMT "<%.3f, %.3f, %.3f>"
#define V4_FMT "<%.3f, %.3f, %.3f, %.3f>"

#define V2_OPEN(v) v.x, v.y
#define V3_OPEN(v) v.x, v.y, v.z
#define V4_OPEN(v) v.x, v.y, v.z, v.w

#define LEN(array) sizeof(array) / sizeof(array[0])

inline const char* TextFormat(const char* text, ...)
{
    const u8 maxBuffers = 4;
    const u16 maxBufferLength = 1024;

    // We create an array of buffers so strings don't expire until MAX_TEXTFORMAT_BUFFERS invocations
    static char buffers[maxBuffers][maxBufferLength] = {0};
    static int index = 0;

    char* currentBuffer = buffers[index];
    memset(currentBuffer, 0, maxBufferLength); // Clear buffer before using

    va_list args;
    va_start(args, text);
    int requiredByteCount = vsnprintf(currentBuffer, maxBufferLength, text, args);
    va_end(args);

    // If requiredByteCount is larger than the MAX_TEXT_BUFFER_LENGTH, then overflow occured
    if (requiredByteCount >= maxBufferLength)
    {
        // Inserting "..." at the end of the string to mark as truncated
        char* truncBuffer = buffers[index] + maxBufferLength - 4; // Adding 4 bytes = "...\0"
        sprintf(truncBuffer, "...");
    }

    index += 1; // Move to next buffer for next function call
    if (index >= maxBuffers)
        index = 0;

    return currentBuffer;
}
