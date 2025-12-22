#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "parser.h"

void generate_code(Program* program, const char* output_filename);

void generate_assignment(FILE* file, ASTNode* node);
void generate_print(FILE* file, ASTNode* node);
void generate_expression(FILE* file, ASTNode* node);
void generate_if(FILE* file, ASTNode* node);

const char* get_operator_string(TokenType op);

#endif
