#include "Core/IO.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <stdio.h>
#include <stdlib.h>

#define IO_READ_CHUNK_SIZE 20971520

File ReadFile(const char* path)
{
    File file;
    file.isValid = false;

    FILE* fileHandle = fopen(path, "rb");
    if (!fileHandle)
    {
        WARN("Failed to read file %s!", path);
        return file;
    }

    char* data = NULL;
    char* temp = NULL;
    u64 used = 0;
    u64 size = 0;
    u64 n = 0;

    while (true)
    {
        if (used + IO_READ_CHUNK_SIZE + 1 > size)
        {
            size = used + IO_READ_CHUNK_SIZE + 1;

            if (size <= used)
            {
                free(data);
                WARN("%s is too large to read!", path);
                return file;
            }

            temp = (char*)realloc(data, size);
            if (!temp)
            {
                free(data);
                WARN("Not enough memory to read file %s!", path);
                return file;
            }

            data = temp;
        }

        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fileHandle);
        if (n == 0)
            break;

        used += n;
    }

    if (!fileHandle)
    {
        free(data);
        WARN("Failed to read file %s!", path);
        return file;
    }

    temp = (char*)realloc(data, used + 1);
    if (!temp)
    {
        free(data);
        WARN("Not enough memory to read file %s!", path);
        return file;
    }

    data = temp;
    data[used] = 0;

    file.data = data;
    file.length = used;
    file.isValid = true;

    fclose(fileHandle);
    return file;
}

void WriteFile(void* buffer, u64 size, const char* path)
{
    FILE* fileHandle = fopen(path, "wb");
    if (!fileHandle)
    {
        WARN("Failed to write file %s!", path);
        return;
    }

    u64 chunksWritten = fwrite(buffer, size, 1, fileHandle);
    fclose(fileHandle);

    if (chunksWritten != 1)
    {
        WARN("Unexpected %ld chunks written!", chunksWritten);
        return;
    }
}
