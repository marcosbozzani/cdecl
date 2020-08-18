#include "global.h"
#include "stream.h"

stream_t *stream_open_file(const char *file, const char *mode)
{
    stream_t *stream = fopen(file, mode);
    if (stream == null)
    {
        fprintf(stderr, "Error opening file: %s", file);
        abort();
    }
    return stream;
}

void stream_close_file(stream_t *stream)
{
    if (!fclose(stream))
    {
        fprintf(stderr, "Error closing file stream");
        abort();
    }
}

stream_t *stream_open_process(const char *command, const char *mode)
{
    stream_t *stream = popen(command, mode);
    if (stream == null)
    {
        fprintf(stderr, "Error opening process: %s", command);
        abort();
    }
    return stream;
}

void stream_close_process(stream_t *stream)
{
    if (pclose(stream) < 0)
    {
        fprintf(stderr, "Error closing process stream");
        abort();
    }
}

int stream_read_all(char **result, stream_t *stream)
{
    char buffer[4096];
    *result = memory_alloc(sizeof(char) * sizeof(buffer));
    **result = '\0';

    while (fgets(buffer, sizeof(buffer), stream) != null)
    {
        size_t new_size = strlen(*result) + 1 + strlen(buffer);
        *result = memory_realloc(*result, new_size);
        strcat(*result, buffer);
    }

    return 0;
}

int stream_read_line(char **result, stream_t *stream)
{
    char buffer[4096];
    *result = memory_alloc(sizeof(char) * sizeof(buffer));
    **result = '\0';

    while (fgets(buffer, sizeof(buffer), stream) != null)
    {
        size_t new_size = strlen(*result) + 1 + strlen(buffer);
        *result = memory_realloc(*result, new_size);
        strcat(*result, buffer);

        size_t result_len = strlen(*result) - 1;
        if ((*result)[result_len] == '\n')
        {
            return ~0;
        }
    }

    return 0;
}