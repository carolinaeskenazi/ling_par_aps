%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);

FILE *output;
%}

%union {
    int num;
    char* str;
}

%token <str> ID STRING
%token <num> NUM

%token VAR INT BOOL SENSOR
%token IF THEN ELSE END WHILE DO
%token PRINT

%token AQUECER DESPEJAR MISTURAR ESPERAR FAZER_CAFE
%token PAGAR LER_SENSOR ALERTA

%token ATRIB
%token EQ NEQ LE GE

%type <num> expression
%type <str> tipo_cafe

%%

program:
    statements
;

statements:
    | statements statement
;

statement:
      VAR ID ':' type ';'                  { fprintf(output, "VAR %s\n", $2); }
    | ID ATRIB expression ';'              { fprintf(output, "MOV %s, %d\n", $1, $3); }
    | IF condition THEN statements else_block END
    | WHILE condition DO statements END
    | AQUECER '(' NUM ')' ';'              { fprintf(output, "AQUECER %d\n", $3); }
    | DESPEJAR '(' STRING ')' ';'          { fprintf(output, "DESPEJAR %s\n", $3); }
    | MISTURAR '(' NUM ')' ';'             { fprintf(output, "MISTURAR %d\n", $3); }
    | ESPERAR '(' NUM ')' ';'              { fprintf(output, "ESPERAR %d\n", $3); }
    | FAZER_CAFE '(' tipo_cafe ')' ';'     { fprintf(output, "FAZER_CAFE %s\n", $3); }
    | PAGAR '(' STRING ')' ';'             { fprintf(output, "PAGAR %s\n", $3); }
    | LER_SENSOR '(' ID ')' ';'            { fprintf(output, "LER_SENSOR %s\n", $3); }
    | ALERTA '(' STRING ')' ';'            { fprintf(output, "ALERTA %s\n", $3); }
    | PRINT '(' STRING ')' ';'             { fprintf(output, "PRINT %s\n", $3); }
;

else_block:
    | ELSE statements
;

condition:
    expression comparator expression
;

expression:
    NUM                                    { $$ = $1; }
;

type:
    INT | BOOL | SENSOR
;

comparator:
    EQ | NEQ | '<' | '>' | LE | GE
;

tipo_cafe:
    STRING
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}