%{
    #include <stdio.h>
    #include <stdlib.h>

    int stack[10];
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
    void out(){
        printf("The contents of the stack are: ");
        int i=0;
        for(i;i<top;i++){
            printf("%d ", stack[i]);
        }
        printf("%d\n", stack[top]);
    }

%}

%union {
    int intval;
}

%token <intval> NUM
%token ADD SUB MUL DIV EOL
%start program




%%

program: stmts;

stmts: stmts stmt | stmt;

stmt: EOL
    | NUM {
        if(top == 9){
            printf("Runtime Error: The pop will lead to stack overflow.\n");
            YYABORT;
        }
        else{
            push($1);
            out();
        } 
    }
    | ADD{
        if(top < 1){
            printf("Runtime Error: The pop will lead to stack underflow.\n");
            YYABORT;
        } 
        else{
            push(pop() + pop());
            out();
        } 
    }
    | SUB{
        if(top < 1){
            printf("Runtime Error: The pop will lead to stack underflow.\n");
            YYABORT;
        } 
        else{
            int a = pop();
            int b = pop();
            push(b - a);
            out();
        } 
    }
    | MUL{
        if(top < 1){
            printf("Runtime Error: The pop will lead to stack underflow.\n");
            YYABORT;
        } 
        else{
            push(pop() * pop());
            out();
        } 
    }
    | DIV{
        if(top < 1){
            printf("Runtime Error: The pop will lead to stack underflow.\n");
            YYABORT;
        } 
        else{
            int a = pop();
            int b = pop();
            push(b / a);
            out();
        } 
    }
    

%%

int main(){
    int error = yyparse();
    /* if(top == 0 && error == 0) printf("%d\n", pop()); */

    return 0;
}