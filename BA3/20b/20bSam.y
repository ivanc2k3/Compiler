%{
    #include <stdio.h>
    #include <stdlib.h>
    #define MAX_STACK 99999
    int yylex();
    void yyerror(const char* message) {};
    float ans;
%}

%union{
    float intval;
}

%type <intval> stmt

%token <intval> NUM
%token ADD SUB MUL DIV 

%start expr
%%
expr: stmt
stmt: NUM{
        $$ = $1;
    }
    | stmt stmt ADD{
        ans = $1 + $2;
        $$ = ans;
    }
    | stmt stmt SUB{
        ans = $1 - $2;
        $$ = ans;
    }
    | stmt stmt MUL{
        ans = $1 * $2;
        $$ = ans;
    }
    | stmt stmt DIV{
        ans = $1 / $2;
        $$ = ans;
    }

%%

int main(int argc, char **argv) {
    int error = yyparse(); // yyparse() returns 0 if parsing is successful
    if(!error){
        printf("%.1f\n", ans);
    } else{
        printf("Wrong Formula\n");
    }
    return 0;
}