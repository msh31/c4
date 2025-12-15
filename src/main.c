#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // printf("hello world!");

    if(argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(filesize + 1); //+1 for null terminator "\0"
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    printf("%s\n", buffer);
    fclose(file);
    free(buffer);
    return 0;
}
