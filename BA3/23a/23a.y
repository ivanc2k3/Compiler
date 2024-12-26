%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s) {};
    int error = 0;
    double ret = 0;
%}

%union {
    double num;
}

%type <num> ANS
%token <num> NUM 
%token ADD SUB MUL DIV

%left ADD SUB
%left MUL DIV

%start stmts

%%
stmts: ANS
ANS: ANS ADD ANS {
        ret = $1 + $3;
        $$ = $1 + $3;
    }
    | ANS SUB ANS {
        ret = $1 - $3;
        $$ = $1 - $3;
    }
    | ANS MUL ANS {
        ret = $1 * $3;
        $$ = $1 * $3;
    }
    | ANS DIV ANS {
        if($3 == 0){
            YYABORT;
        }
        else{
            ret = $1 / $3;
            $$ = $1 / $3;
        } 
    }
    | NUM{
        $$ = $1;
    }

%%

int main(){
    int error = yyparse();
    if(error != 0) printf("Invalid Value");
    else printf("%.3f", ret);
    return 0;
}