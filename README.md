# ling_par_aps

A VM que escolhi é de uma máquina de café, em que o usuario seleciona a opção de café desejada e a máquina produz.

# Linguagem estruturada segundo a EBNF:

```bash
program ::= { statement } ;

statement ::= var_decl
            | assign
            | if_stmt
            | while_stmt
            | action_stmt
            | print_stmt ;

var_decl ::= "var", identifier, ":", type, ";" ;

assign ::= identifier, ":=", expression, ";" ;

if_stmt ::= "if", condition, "then", { statement }, [ "else", { statement } ], "end" ;

while_stmt ::= "while", condition, "do", { statement }, "end" ;

action_stmt ::= "aquecer", "(", number, ")", ";"
              | "despejar", "(", string, ")", ";"
              | "misturar", "(", number, ")", ";"
              | "esperar", "(", number, ")", ";"
              | "fazer_cafe", "(", tipo_cafe, ")", ";"
              | "pagar", "(", metodo_pagamento, ")", ";"
              | "ler_sensor", "(", identifier, ")", ";"
              | "alerta", "(", string, ")", ";" ;

print_stmt ::= "print", "(", string, ")", ";" ;

condition ::= expression, comparator, expression ;

expression ::= term, { ("+" | "-"), term } ;

term ::= factor, { ("*" | "/"), factor } ;

factor ::= number
         | identifier
         | "(", expression, ")" ;

type ::= "int" | "bool" | "sensor" ;

comparator ::= "=" | "<>" | "<" | ">" | "<=" | ">=" ;

tipo_cafe ::= '"expresso"' 
            | '"cappuccino"' 
            | '"latte"' 
            | '"mocha"' 
            | '"americano"' ;

metodo_pagamento ::= '"cartao"' 
                   | '"pix"' 
                   | '"dinheiro"' ;

identifier ::= letter, { letter | digit | "_" } ;

number ::= digit, { digit } ;

string ::= '"', { character }, '"' ;

letter ::= "A" | "B" | ... | "Z"
        | "a" | "b" | ... | "z" ;

digit ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

character ::= ? qualquer caractere visível, exceto aspas duplas ? ;
```

# Exemplo - Fazer um expresso:

var temperatura: int;
var agua_pronta: bool;

temperatura := 90;
agua_pronta := true;

if agua_pronta = true then
    aquecer(temperatura);
    fazer_cafe("expresso");
    print("Café expresso pronto!");
end
