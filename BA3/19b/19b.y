%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    
    int error = 0;

    int yylex();
    void yyerror(char *s) {};
    

%}

%union {
    double intval;
}
%type <intval>stmt
%token <intval> NUM
%token HAT ADD SUB LBR RBR FRAC
%start program

%left ADD SUB
%left HAT
%left LBR RBR
%left FRAC


%%

program: stmt{printf("%.3f", $1);}


stmt: stmt ADD stmt{
        $$ = $1 + $3;
    }
    | stmt SUB stmt{
        $$ = $1 - $3;
    }
    | LBR stmt RBR{
        $$ = $2;
    }
    | FRAC LBR stmt RBR LBR stmt RBR{
        $$ = $3 / $6;
    }
    | stmt HAT stmt{
        $$ = pow($1, $3);
    }
    | NUM{
        $$ = $1;
    }

%%

int main(){
    int error = yyparse();

    

    return 0;
}