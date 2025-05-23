%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
"int"           { return INT; }
"boolean"       { return BOOLEAN; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"true"          { return TRUE; }
"false"         { return FALSE; }

[0-9]+          { yylval.num = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return ID; }

"="             { return ASSIGN; }
";"             { return SEMI; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }

[ \t\r\n]+      ; // Ignore whitespace

.               { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
