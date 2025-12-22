#include "lexer.h"

#include <stdio.h>
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
            tmp.type = TOKEN_NUMBER;
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
            
            Token tmp;
            if (strcmp(chr_str, "print") == 0) {
                tmp.type = TOKEN_PRINT;
            } else if (strcmp(chr_str, "if") == 0) {
                tmp.type = TOKEN_IF;
            } else if (strcmp(chr_str, "then") == 0) {
                tmp.type = TOKEN_THEN;
            } else if (strcmp(chr_str, "end") == 0) {
                tmp.type = TOKEN_END;
            } else {
                tmp.type = TOKEN_IDENTIFIER;
            }

            tmp.value = chr_str;

            tokens[*token_count] = tmp;
            (*token_count)++;
        } else if(source[current_position] == ';') {
            Token tmp;
            tmp.type = TOKEN_SEMICOLON;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == '+') {

            Token tmp;
            tmp.type = TOKEN_PLUS;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == '-') {
            Token tmp;
            tmp.type = TOKEN_MINUS;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == '*') {
            Token tmp;
            tmp.type = TOKEN_MULTIPLY;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == '/') {
            Token tmp;
            tmp.type = TOKEN_DIVIDE;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == '(') {
            Token tmp;
            tmp.type = TOKEN_LEFT_PAREN;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == ')') {
            Token tmp;
            tmp.type = TOKEN_RIGHT_PAREN;
            tmp.value = NULL; 

            tokens[*token_count] = tmp;
            (*token_count)++;
            current_position++;
        } else if (source[current_position] == ':') {
            if(source[current_position + 1] == '=') {
                Token tmp;
                tmp.type = TOKEN_COLON_EQUALS;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position += 2;
            } else {
                fprintf(stderr, "Lexical error at position %zu: unexpected character '%c' after ':'\n", current_position, source[current_position + 1]);
                return NULL; 
            }
        } else if (source[current_position] == '=') {
            if(source[current_position + 1] == '=') {
                Token tmp;
                tmp.type = TOKEN_EQUALS;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position += 2;
            } else {
                fprintf(stderr, "Lexical error at position %zu: unexpected character '%c' after '='\n", current_position, source[current_position + 1]);
                return NULL; 
            }
        } else if (source[current_position] == '!') {
            if(source[current_position + 1] == '=') {
                Token tmp;
                tmp.type = TOKEN_NOT_EQUALS;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position += 2;
            } else {
                fprintf(stderr, "Lexical error at position %zu: unexpected character '%c' after '!'\n", current_position, source[current_position + 1]);
                return NULL; 
            }
        } else if (source[current_position] == '<') {
            if(source[current_position + 1] == '=') {
                Token tmp;
                tmp.type = TOKEN_LESS_EQUAL;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position += 2;
            } else {
                Token tmp;
                tmp.type = TOKEN_LESS_THAN;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position++;
            }
        } else if (source[current_position] == '>') {
            if(source[current_position + 1] == '=') {
                Token tmp;
                tmp.type = TOKEN_GREATER_EQUAL;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position += 2;
            } else {
                Token tmp;
                tmp.type = TOKEN_GREATER_THAN;
                tmp.value = NULL; 

                tokens[*token_count] = tmp;
                (*token_count)++;
                current_position++;
            }
        } else {
            current_position++;
        }
    }

    return tokens;
}
