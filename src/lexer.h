typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_COLON_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DIVIDE,
    TOKEN_MULTIPLY,
    TOKEN_SEMICOLON,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_PRINT,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

Token* tokenize(const char *source, int *token_count);
