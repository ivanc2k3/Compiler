%{
    #include <stdio.h>
    #include <stdlib.h>

    double stack[1008];
    int top = -1;
    int error = 0;

    int yylex();
    void yyerror(char *s) {};
    void push(double num){
        stack[++top] = num;
    }
    double pop(){
        if(top < 0){
            exit(1);
        }
        return stack[top--];
    }

%}

%union {
    double intval;
}

%token <intval> NUM
%token EOL ADD SUB MUL DIV
%start program




%%

program: stmts;

stmts: stmts stmt | stmt;

stmt: EOL
    | NUM {
        push($1);
    }
    | ADD{
        if(top < 1) YYABORT;
        else push(pop() + pop());
    }
    | SUB{
        if(top < 1) YYABORT;
        else push(-(pop() - pop()));
    }
    | MUL{
        if(top < 1) YYABORT;
        else push(pop() * pop());
    }
    | DIV{
        if(top < 1) YYABORT;
        else{
            double a = pop();
            double b = pop();
            push(b / a);
        }
    }
    

%%

int main(){
    int error = yyparse();
    /* printf("%d", top); */
    if(top == 0 && error == 0) printf("%.1f\n", pop());
    else printf("Wrong Formula");

    return 0;
}