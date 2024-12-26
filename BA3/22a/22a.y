%{
    #include <stdio.h>
    #include <stdlib.h>


    int error = 0;
    int ans = 0;

    int yylex();
    void yyerror(char *s) {};
    int per(int a){
        int ret=1, i=1;
        for(i; i<=a;i++) ret *= i;
        return ret;
    }
    

%}

%union {
    int intval;
}

%type <intval> stmt
%token <intval> NUM
%token ADD SUB PER COM
%start program


%left ADD SUB
%left PER COM

%%

program: stmt;


stmt: stmt ADD stmt{
        ans = $1 + $3;
        $$ = ans;
    }
    | stmt SUB stmt{
        ans = $1 - $3;
        $$ = ans;
    }
    | PER NUM NUM{
        int n = $2;
        int k = $3;
        ans = per(n) / per(n - k);
        $$ = ans;
    }
    | COM NUM NUM{
        int n = $2;
        int m = $3;
        ans = per(n) / (per(m) * per(n - m));
        $$ = ans;
    }

%%

int main(){
    int error = yyparse();
    if(error == 0) printf("%d\n", ans);
    else printf("Wrong Formula");

    return 0;
}