#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

void free_tokens(Token* tokens, int token_count) {
    if (tokens == NULL || token_count == 0) {
        printf("No tokens were found to free!!\n");
    } else {
        for (int i = 0; i < token_count; i++) {
            if(tokens[i].value != NULL) {
                free(tokens[i].value);
            }
        }
        free(tokens);
    }
}

int cleanup(FILE* file, char* buffer) {
    fclose(file);
    int result = system("gcc output.c -o program");
    if (result != 0) {
        fprintf(stderr, "Error: compilation failed\n");
        return 1;
    }
    remove("output.c");
    free(buffer);
    return 0;
}

int main(int argc, char* argv[]) {
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

    int token_count;
    Token *tokens = tokenize(buffer, &token_count);

    if (tokens == NULL || token_count == 0) {
        printf("womp womp\n");
    } else {
        printf("Found %d tokens\n", token_count);

        for (int i = 0; i < token_count; i++) {
            printf("type: %d\n", tokens[i].type);
            printf("value: %s\n", tokens[i].value); 
        }
    }

    Program* parsedTokens = parse_tokens(tokens, token_count);

    if (parsedTokens == NULL) {
        printf("Parsing error\n");
    } else {
        printf("Parsed %d statements!\n", parsedTokens->statement_count);
    }

    generate_code(parsedTokens, "output.c");
    free_tokens(tokens, token_count);
    return cleanup(file, buffer);
}
