#include "codegen.h"
#include "parser.h"
#include <stdio.h>

void generate_code(Program* program, const char* output_filename) {
    FILE *file = fopen(output_filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", output_filename);
        return;
    }

    fprintf(file, "// This code was generated using c4t, the c4 to c transpiler\n");
    fprintf(file, "// The C4 language and it's transpiler were made by msh31 / marco007!\n\n");
    fprintf(file, "#include <stdio.h>\n\n");
    fprintf(file, "int main() {\n");

    for (int i = 0; i < program->statement_count; i++) {
        ASTNode* stmt = program->statements[i];

        if (stmt->type == NODE_ASSIGNMENT) {
            generate_assignment(file, stmt);
        } else if (stmt->type == NODE_EXPRESSION) {
            generate_print(file, stmt); //print is the only expression we support rn
        }
    }

    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    // fprintf(file, );
    
    fclose(file);
    printf("code generated!");
}

void generate_assignment(FILE* file, ASTNode* node) {
    fprintf(file, "    int "); //yes, only integers rn
    
    fprintf(file, "%s", node->data.assignment.variable);
    fprintf(file, " = ");

    ASTNode* expr = node->data.assignment.expression;
    generate_expression(file, expr);

    fprintf(file, ";\n");
}

void generate_print(FILE* file, ASTNode* node) {
    fprintf(file, "    printf(\"%%d\\n\", ");
    generate_expression(file, node->data.print_stmt.expression);
    fprintf(file, ");\n");
}

void generate_expression(FILE* file, ASTNode* node) {
    if(node->type != NODE_NUMBER) {
       return; 
    }

    fprintf(file, "%d", node->data.number_value);
}
