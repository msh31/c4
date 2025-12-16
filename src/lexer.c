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
        } else if (isdigit(source[current_position])) {
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
        } else if(isalpha(source[current_position])) {
            int start = current_position;
            while (isalnum(source[current_position])) {
                current_position++;
            }
            int length = current_position - start;

            char* chr_str = malloc(length + 1);
            strncpy(chr_str, &source[start], length);
            chr_str[length] = '\0';

            int res = strcmp(chr_str, "print");
            if(res != 0) {
                Token tmp;
                tmp.type = IDENTIFIER;
                tmp.value = chr_str;

                tokens[*token_count] = tmp;
                (*token_count)++;
            } else {
                Token tmp;
                tmp.type = PRINT;
                tmp.value = chr_str;

                tokens[*token_count] = tmp;
                (*token_count)++;
            }
        } else if(source[current_position] == ';') {
            Token tmp;
            tmp.type = SEMICOLON;
            tmp.value = ";";

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else {
            current_position++;
        }
    }

    return tokens;
}
