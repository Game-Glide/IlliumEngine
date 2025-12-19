#include <io/io.h>
#include <stdlib.h>
#include <stdio.h>

char *read_file(const char *file_path) {
    FILE* fptr;
    fptr = fopen(file_path, "rb");

    if (fptr == NULL) {
        fprintf(stderr, "failed to open file: %s", file_path);
    }

    fseek(fptr, 0, SEEK_END);
    long file_size = ftell(fptr);
    rewind(fptr);

    if (file_size <= 0) {
        fprintf(stderr, "Error: Empty or invalid file size for %s\n", file_path);
        fclose(fptr);
    }

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fptr);
    }

    size_t bytes_read = fread(buffer, 1, file_size, fptr);
    buffer[bytes_read] = '\0';

    fclose(fptr);
    return buffer;
}
