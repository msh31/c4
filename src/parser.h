#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

//tags for the types
typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    NODE_EXPRESSION,
    NODE_IF,
} NodeType;

typedef struct {
    Token *tokens;
    int current;
    int token_count; 
} Parser;

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
        struct {
            struct ASTNode *condition;
            struct ASTNode **body;
            int body_count;
        } if_stmt;
    } data;
} ASTNode;

typedef struct {
    ASTNode **statements;
    int statement_count;
} Program;

ASTNode* create_number(int value);
ASTNode* create_variable(char* name);
ASTNode* create_binary_op(TokenType op, ASTNode* left, ASTNode* right);
ASTNode* create_assignment(char* variable, ASTNode* expression);
ASTNode* create_print(ASTNode* expression);
ASTNode* create_if(ASTNode* condition, ASTNode** body, int body_count);

Program* parse_tokens(Token* tokens, int token_count);

Token* get_current_token(Parser* parser);
Token* move_to_next_token(Parser* parser);
int are_all_tokens_parsed(Parser* parser);

ASTNode* parse_assignment(Parser* parser);
ASTNode* parse_print(Parser* parser);
ASTNode* parse_factor(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_comparison(Parser* parser);
ASTNode* parse_if(Parser* parser);

#endif
