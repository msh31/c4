#include "codegen.h"

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
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    // fprintf(file, );
    
    fclose(file);
    printf("code generated!");
}
