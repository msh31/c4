#include "lexer.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Token* tokenize(const char *source, int *token_count) {
    Token *tokens = malloc(100 * sizeof(Token));
    *token_count = 0;
    int current_position = 0;

    // ' = character literals
    // " = string literals
    // since the null term is a character, it has be single quotes...
    while(source[current_position] != '\0') {
        char current = source[current_position];

        if (isspace(source[current_position])) {
            current_position++;
            continue;
        }

        if (isdigit(source[current_position])) {
            int start = current_position;
            while (isdigit(source[current_position])) {
                current_position++;
            }
            int length = current_position - start;

            char* num_str = malloc(length + 1);
            strncpy(num_str, &source[start], length);
            num_str[length] = '\0';

            Token tmp;
            tmp.type = NUMBER;
            tmp.value = num_str;

            tokens[*token_count] = tmp;
            (*token_count)++;
        }
    }

    //free the memory?
    return tokens;
}
