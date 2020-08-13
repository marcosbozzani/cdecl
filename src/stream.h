#pragma once

#include <stdio.h>

typedef FILE stream_t;

stream_t *stream_open_file(const char *file, const char *mode);
void stream_close_file(stream_t *stream);
stream_t *stream_open_process(const char *command, const char *mode);
void stream_close_process(stream_t *stream);
int stream_read_all(char **result, stream_t *stream);
int stream_read_line(char **result, stream_t *stream);