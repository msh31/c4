#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

//tags for the types
typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    NODE_EXPRESSION
} NodeType;

typedef struct ASTNode {
    NodeType type;
    
    union {
        int number_value;
        char* variable_name;
        struct {
            TokenType opps;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        struct {
            char* variable;
            struct ASTNode *expression;
        } assignment;
        struct {
            struct ASTNode *expression;
        } print_stmt;
    } data;
} ASTNode;

#endif
