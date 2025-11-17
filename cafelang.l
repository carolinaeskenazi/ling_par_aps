%{
#include "cafelang.tab.h"
#include <string.h>
%}

digit       [0-9]
letter      [a-zA-Z]
id          {letter}({letter}|{digit}|_)*
string      \"([^"])*\"

%%

"var"           { return VAR; }
"int"           { return INT; }
"bool"          { return BOOL; }
"sensor"        { return SENSOR; }

"true"          { yylval.num = 1; return NUM; }
"false"         { yylval.num = 0; return NUM; }

"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"end"           { return END; }

"while"         { return WHILE; }
"do"            { return DO; }

"print"         { return PRINT; }

"aquecer"       { return AQUECER; }
"despejar"      { return DESPEJAR; }
"misturar"      { return MISTURAR; }
"esperar"       { return ESPERAR; }
"fazer_cafe"    { return FAZER_CAFE; }
"pagar"         { return PAGAR; }
"ler_sensor"    { return LER_SENSOR; }
"alerta"        { return ALERTA; }

":="            { return ATRIB; }
":"             { return ':'; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }

"="             { return EQ; }
"<>"            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return '<'; }
">"             { return '>'; }

{id}            { yylval.str = strdup(yytext); return ID; }
{digit}+        { yylval.num = atoi(yytext); return NUM; }
{string}        { yylval.str = strdup(yytext); return STRING; }

\#[^\n]*        { /* ignora comentários com '#' */ }
[ \t\n\r]+      { /* ignora espaços */ }

.               { printf("Caractere inválido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
