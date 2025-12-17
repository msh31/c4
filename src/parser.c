#include "parser.h"
#include <cstdlib>
#include <stdlib.h>

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
