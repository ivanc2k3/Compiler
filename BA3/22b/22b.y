%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s) {};
    int error = 0;
    int ret = 0;
%}

%union {
    int num;
}

%type <num> BOO ANDSUB ORSUB
%token <num> NUM 
%token AND1 AND2 OR1 OR2 NOT1 NOT2

%left AND1 AND2 OR1 OR2
%left NOT1 NOT2

%start stmts

%%
stmts: BOO
BOO: AND1 ANDSUB AND2{
        ret = 1 && $2;
        $$ = ret;
    }
    | AND1 AND2{
        ret = 1;
        $$ = 1;
    }
    | OR1 ORSUB OR2{
        ret = 0 || $2;
        $$ = ret;
    }
    | OR1 OR2{
        ret = 0;
        $$ = 0;
    }
    | NOT1 BOO NOT2{
        ret = !$2;
        $$ = !$2;
    }
    | NUM{
        ret = $1;
        $$ = $1;
    }
ANDSUB: BOO ANDSUB{
        ret = $1 && $2;
        $$ = ret;
    }
    | BOO{
        ret = $1;
        $$ = ret;
    }
ORSUB: BOO ORSUB{
        ret = $1 || $2;
        $$ = ret;
    }
    | BOO{
        ret = $1;
        $$ = ret;
    }

%%

int main(){
    int error = yyparse();
    if(error == 0){
        if(ret == 1) printf("true");
        else printf("false");
    } 
    else printf("Invalid");
    return 0;
}