%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s) {};
    int error = 0;
    double ret = 0;
    double f(double x){
        return 4*x-1;
    }
    double g(double x, double y){
        return 2*x+y-5;
    }
    double h(double x, double y, double z){
        return 3*x-5*y+z;
    }
%}

%union {
    double num;
}

%type <num> ANS
%token <num> NUM 
%token H F G LPR RPR COM

%left H F G
%left LPR RPR


%start stmts

%%
stmts: ANS{printf("%.3f", $1);}
ANS: H LPR ANS COM ANS COM ANS RPR {
        ret = h($3, $5, $7);
        $$ = ret;
    }
    | G LPR ANS COM ANS RPR{
        ret = g($3, $5);
        $$ = ret;
    }
    | F LPR ANS RPR {
        ret = f($3);
        $$ = ret;
    }
    | NUM{
        $$ = $1;
    }

%%

int main(){
    int error = yyparse();
    if(error != 0) printf("Invalid");
    return 0;
}