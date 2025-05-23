%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

FILE *infile;
FILE *outfile;
%}

%union {
    int num;
    char *str;
}

%token <num> NUM
%token <str> ID
%token INT BOOLEAN IF ELSE WHILE TRUE FALSE
%token ASSIGN SEMI LPAREN RPAREN LBRACE RBRACE
%token PLUS MINUS MUL DIV

%type <num> expr

%right ASSIGN
%left PLUS MINUS
%left MUL DIV
%nonassoc IFX
%nonassoc ELSE

%start program

%%

program:
    statements
;

statements:
      /* empty */
    | statements statement
;

statement:
      INT ID SEMI                        { fprintf(outfile, "Declare int %s\n", $2); free($2); }
    | ID ASSIGN expr SEMI               { fprintf(outfile, "Assign %s = %d\n", $1, $3); free($1); }
    | IF LPAREN expr RPAREN statement %prec IFX
    | IF LPAREN expr RPAREN statement ELSE statement
    | WHILE LPAREN expr RPAREN statement
    | LBRACE statements RBRACE
;

expr:
      expr PLUS expr                    { $$ = $1 + $3; }
    | expr MINUS expr                   { $$ = $1 - $3; }
    | expr MUL expr                     { $$ = $1 * $3; }
    | expr DIV expr                     { $$ = $1 / $3; }
    | NUM                               { $$ = $1; }
    | ID                                { $$ = 0; }
    | TRUE                              { $$ = 1; }
    | FALSE                             { $$ = 0; }
    | LPAREN expr RPAREN                { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(outfile, "Syntax error: %s\n", s);
}

int main() {
    extern FILE *yyin;
    
    infile = fopen("input.txt", "r");
    outfile = fopen("output.txt", "w");

    if (!infile) {
        perror("Failed to open input.txt");
        exit(EXIT_FAILURE);
    }
    if (!outfile) {
        perror("Failed to open output.txt");
        exit(EXIT_FAILURE);
    }

    yyin = infile;

    yyparse();

    fclose(infile);
    fclose(outfile);
    return 0;
}
