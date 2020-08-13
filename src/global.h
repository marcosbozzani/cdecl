#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define null NULL

static inline void *memory_alloc(size_t size)
{
    void *memory = malloc(size);
    if (memory == null)
    {
        fprintf(stderr, "malloc failed");
        abort();
    }
    return memory;
}

static inline void *memory_realloc(void *memory, size_t size)
{
    memory = realloc(memory, size);
    if (memory == null)
    {
        fprintf(stderr, "realloc failed");
        abort();
    }
    return memory;
}

#define memory_free(memory) if (memory != null) free(memory); memory = null;