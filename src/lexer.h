typedef enum {
    IDENTIFIER,
    NUMBER,
    COLON_EQUALS,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    SEMICOLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    PRINT
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

Token* tokenize(const char *source, int *token_count);
