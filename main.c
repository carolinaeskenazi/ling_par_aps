#include <stdio.h>

extern FILE *yyin;
extern FILE *output;

int yyparse();

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: ./cafelang arquivo.cafe\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    output = fopen("output.asm", "w");

    if (!yyin || !output) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    yyparse();

    fclose(yyin);
    fclose(output);
    printf("Compilado com sucesso para output.asm\n");
    return 0;
}