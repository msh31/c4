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
        } else if(get_current_token(&p)->type == TOKEN_IF) {
            ASTNode* stmt = parse_if(&p);
            pg->statements[pg->statement_count] = stmt;
            pg->statement_count++;
        }else {
            move_to_next_token(&p);
        }
    }

    return pg;
}

ASTNode* parse_factor(Parser* parser) {
    if(get_current_token(parser)->type == TOKEN_NUMBER) {
        int value = atoi(get_current_token(parser)->value);
        ASTNode* node = create_number(value);
        move_to_next_token(parser);

        return node;
    } else if(get_current_token(parser)->type == TOKEN_IDENTIFIER) {
        char* variable_name = get_current_token(parser)->value;
        ASTNode* node = create_variable(variable_name);
        move_to_next_token(parser);

        return node;
    } else if(get_current_token(parser)->type == TOKEN_LEFT_PAREN) {
        move_to_next_token(parser);
        ASTNode* node = parse_expression(parser);

        if(get_current_token(parser)->type == TOKEN_RIGHT_PAREN) {
            move_to_next_token(parser);
        }

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
        expr = parse_comparison(parser);
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
        expr = parse_comparison(parser);

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

ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);

    while(get_current_token(parser)->type == TOKEN_MULTIPLY || get_current_token(parser)->type == TOKEN_DIVIDE) {
        TokenType op = get_current_token(parser)->type;
        move_to_next_token(parser);

        ASTNode* right = parse_factor(parser);
        ASTNode* result = create_binary_op(op, left, right); 

        left = result;
    }

    return left;
}

ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);

    while(get_current_token(parser)->type == TOKEN_PLUS || get_current_token(parser)->type == TOKEN_MINUS) {
        TokenType op = get_current_token(parser)->type;
        move_to_next_token(parser);

        ASTNode* right = parse_term(parser);
        ASTNode* result = create_binary_op(op, left, right); 

        left = result;
    }

    return left;
}

ASTNode* parse_comparison(Parser* parser) {
    ASTNode* left = parse_expression(parser);

    while(get_current_token(parser)->type == TOKEN_LESS_THAN ||
          get_current_token(parser)->type == TOKEN_GREATER_THAN ||
          get_current_token(parser)->type == TOKEN_EQUALS ||
          get_current_token(parser)->type == TOKEN_NOT_EQUALS ||
          get_current_token(parser)->type == TOKEN_LESS_EQUAL ||
          get_current_token(parser)->type == TOKEN_GREATER_EQUAL) {
        
        TokenType op = get_current_token(parser)->type;
        move_to_next_token(parser);

        ASTNode* right = parse_expression(parser);
        left = create_binary_op(op, left, right);
    }

    return left; 
}

ASTNode* parse_if(Parser* parser) {
    if(get_current_token(parser)->type != TOKEN_IF) {
        return NULL;
    }
    move_to_next_token(parser);
    
    if(get_current_token(parser)->type != TOKEN_LEFT_PAREN) {
        return NULL;
    }
    move_to_next_token(parser);
    ASTNode* condition = parse_comparison(parser);
    
    if(get_current_token(parser)->type != TOKEN_RIGHT_PAREN) {
        return NULL;
    }
    move_to_next_token(parser);

    if(get_current_token(parser)->type != TOKEN_THEN) {
        return NULL;
    }
    move_to_next_token(parser);
    ASTNode** body = malloc(100 * sizeof(ASTNode*));
    int body_count = 0;

    while (get_current_token(parser)->type != TOKEN_END) {
        if(get_current_token(parser)->type == TOKEN_IDENTIFIER) {
            ASTNode* stmt = parse_assignment(parser);
            body[body_count] = stmt;
            body_count++;
        } else if(get_current_token(parser)->type == TOKEN_PRINT) {
            ASTNode* stmt = parse_print(parser);
            body[body_count] = stmt;
            body_count++;
        } else if(get_current_token(parser)->type == TOKEN_IF) {
            ASTNode* stmt = parse_if(parser);
            body[body_count] = stmt;
            body_count++;
        } else {
            move_to_next_token(parser);
        }
    }

    move_to_next_token(parser);
    return create_if(condition, body, body_count);
}

ASTNode* create_if(ASTNode* condition, ASTNode** body, int body_count) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = NODE_IF;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.body = body;
    node->data.if_stmt.body_count = body_count;

    return node;
}
