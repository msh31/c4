#include "parser.h"
#include "lexer.h"
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
        } else {
            move_to_next_token(&p);
        }
    }

    return pg;
}

ASTNode* parse_expression(Parser* parser) {
    if(get_current_token(parser)->type == TOKEN_NUMBER) {
        int value = atoi(get_current_token(parser)->value);
        ASTNode* node = create_number(value);
        move_to_next_token(parser);

        return node;
    } else {
        return NULL;
    }
}

ASTNode* parse_assignment(Parser* parser) {
    char* variable_name = get_current_token(parser)->value;
    move_to_next_token(parser);
    ASTNode* expr = NULL;

    if(get_current_token(parser)->type == TOKEN_COLON_EQUALS) {
        move_to_next_token(parser);
        expr = parse_expression(parser);
    } else {
        return NULL;
    }

    if(get_current_token(parser)->type == TOKEN_SEMICOLON) {
        move_to_next_token(parser);
    } else {
        return NULL;
    }

    return create_assignment(variable_name, expr);
}

ASTNode* parse_print(Parser* parser) {
    move_to_next_token(parser);
    ASTNode* expr = NULL;

    if(get_current_token(parser)->type == TOKEN_LEFT_PAREN) {
        move_to_next_token(parser);
        expr = parse_expression(parser);

        if(get_current_token(parser)->type == TOKEN_RIGHT_PAREN) {
            move_to_next_token(parser);

            if(get_current_token(parser)->type == TOKEN_SEMICOLON) {
                move_to_next_token(parser);
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }

    return create_print(expr);
}
