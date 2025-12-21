main:
	gcc -std=c99 src/main.c src/lexer.c src/parser.c src/codegen.c -o transpiler
