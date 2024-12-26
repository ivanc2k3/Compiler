%{
    #include <stdio.h>
    #include <stdlib.h>

    int stack[1008];
    int top = -1;
    int error = 0;

    int yylex();
    void yyerror(char *s) {};
    void push(int num){
        stack[++top] = num;
    }
    int pop(){
        if(top < 0){
            exit(1);
        }
        return stack[top--];
    }

%}

%union {
    int intval;
}

%token <intval> NUM
%token EOL LOAD ADD SUB MUL INC DEC MOD
%start program




%%

program: stmts;

stmts: stmts stmt | stmt;

stmt: EOL
    | LOAD NUM {
        push($2);
    }
    | ADD{
        if(top < 1) YYABORT;
        else push(pop() + pop());
    }
    | SUB{
        if(top < 1) YYABORT;
        else push(pop() - pop());
    }
    | MUL{
        if(top < 1) YYABORT;
        else push(pop() * pop());
    }
    | MOD{
        if(top < 1) YYABORT;
        else push(pop() % pop());
    }
    | INC{
        if(top < 0) YYABORT;
        else push(pop() + 1);
    }
    | DEC{
        if(top < 0) YYABORT;
        else push(pop() - 1);
    }

%%

int main(){
    int error = yyparse();
    if(top == 0 && error == 0) printf("%d\n", pop());
    else printf("Invalid format");

    return 0;
}