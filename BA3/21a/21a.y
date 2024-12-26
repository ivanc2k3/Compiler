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
%token PUSH INV INC DEC
%start program




%%

program: stmts;

stmts: stmts stmt | stmt;

stmt: PUSH NUM {
        push($2);
    }
    | INC{
        if(top < 0) YYABORT;
        else push(pop() + 1);
    }
    | DEC{
        if(top < 0) YYABORT;
        else push(pop() - 1);
    }
    | INV{
        if(top < 1) YYABORT;
        else{
            int a = pop();
            int b = pop();
            push(a);push(b);
        }
    }

%%

int main(){
    int error = yyparse();
    if(error == 0) printf("%d\n", pop());
    else printf("Invalid format");

    return 0;
}