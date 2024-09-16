#pragma once
#include "Core/Base.h"

struct File
{
    char* data;
    u64 length;
    b8 isValid;
};

File ReadFile(const char* path);
void WriteFile(void* buffer, u64 size, const char* path);
