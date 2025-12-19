#include "parser.h"
#include "lexer.h"
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

ASTNode* create_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_NUMBER;
    node->data.number_value = value;

    return node;
}

ASTNode* create_variable(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_VARIABLE;
    node->data.variable_name = name;

    return node;
}

ASTNode* create_binary_op(TokenType op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_BINARY_OP;
    node->data.binary_op.opps = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;

    return node;
}

ASTNode* create_assignment(char* variable, ASTNode* expression) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_ASSIGNMENT; 
    node->data.assignment.variable = variable;
    node->data.assignment.expression = expression;

    return node;
}


ASTNode* create_print(ASTNode* expression) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_EXPRESSION; 
    node->data.print_stmt.expression = expression;

    return node;
}

Token* get_current_token(Parser* parser) {
    return &parser->tokens[parser->current];
}

Token* move_to_next_token(Parser* parser) {
   if(are_all_tokens_parsed(parser)) {
        return get_current_token(parser);
   } else {
        parser->current += 1;
        return &parser->tokens[parser->current];
   }
}

int are_all_tokens_parsed(Parser* parser) {
    // if(memcmp(parser->current, parser->token_count, sizeof(parser->token_count))) {
    //
    // }

    if(parser->current >= parser->token_count) {
        return 1;
    } else {
        return 0;
    }
}


Program* parse_tokens(Token* tokens, int token_count) {
    Parser p;
    p.current = 0;
    p.tokens = tokens;
    p.token_count = token_count;

    Program* pg = malloc(sizeof(Program));
    pg->statement_count = 0;
    pg->statements = malloc(100 * sizeof(ASTNode*));
    
    while (!are_all_tokens_parsed(&p)) {
        if(get_current_token(&p)->type == TOKEN_IDENTIFIER) {
            ASTNode* stmt = parse_assignment(&p);
            pg->statements[pg->statement_count] = stmt;
            pg->statement_count++;
        } else if(get_current_token(&p)->type == TOKEN_PRINT) {
            ASTNode* stmt = parse_print(&p);
            pg->statements[pg->statement_count] = stmt;
            pg->statement_count++;
        }
    }

    return pg;
}
