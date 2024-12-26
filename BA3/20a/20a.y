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
    int zflag = 0;
%}

%union {
    int intval;
}

%token <intval> NUM
%token EOL LOAD ADD SUB MUL DIV INC DEC MOD COPY DELETE SWITCH
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
    | DIV{
        if(top < 1) YYABORT;
        else{
            int a = pop();
            int b = pop();
            if(b==0){
                zflag = 1;
                printf("Divide by zero");
                YYABORT;
            }
            else push(a / b);
        } 
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
    | COPY{
        if(top < 0) YYABORT;
        else push(stack[top]);
    }
    | DELETE{
        if(top < 0) YYABORT;
        else pop();
    }
    | SWITCH{
        if(top < 1) YYABORT;
        else{
            int a = pop();
            int b = pop();
            push(a);
            push(b);
        }
    }
    


%%

int main(){
    int error = yyparse();
    if(top == 0 && error == 0) printf("%d\n", pop());
    else if(zflag != 1) printf("Invalid format");

    return 0;
}