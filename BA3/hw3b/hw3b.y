%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s) {};
    int error = 0;
    int retloc = 0;
%}

%union {
    int location;
    int num;
    struct def{
        int f;
        int s;
    } matrix;
}

%type <matrix> MA
%token <num> NUM
%token <location> ADD SUB MUL
%token LBR RBR LPR RPR TRS COM

%left ADD SUB
%left MUL
%left TRS

%start stmt

%%
stmt: MA
MA: LPR MA RPR {
        $$.f = $2.f;
        $$.s = $2.s;
    }
    | MA ADD MA {
        if($1.f == $3.f && $1.s == $3.s){
            $$.f = $1.f;
            $$.s = $1.s;
        }
        else{
            retloc = $2;
            YYABORT;
        } 
    }
    | MA SUB MA {
        if($1.f == $3.f && $1.s == $3.s){
            $$.f = $1.f;
            $$.s = $1.s;
        }
        else{
            retloc = $2;
            YYABORT;
        } 
    }
    | MA MUL MA {
        if($1.s == $3.f){
            $$.f = $1.f;
            $$.s = $3.s;
        }
        else{
            retloc = $2;
            YYABORT;
        } 
    }
    | MA TRS {
        $$.f = $1.s;
        $$.s = $1.f;
    }
    | LBR NUM COM NUM RBR {
        $$.f = $2;
        $$.s = $4;
    }

%%

int main(){
    int error = yyparse();
    if(error != 0) printf("Semantic error on col %d\n", retloc);
    else printf("Accepted\n");
    return 0;
}