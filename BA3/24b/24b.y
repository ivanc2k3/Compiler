%{
    #include <stdio.h>
    #include <stdlib.h>

    int stack[21];
    int top = -1;
    int error = 0;
    int ipt[21] = {0}; // greater 0
    int iptid = 0;
    int maxval=0;
    int iptleg = 0;

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
    void pass(int i){
        printf("Train %d passing through\n", i);
    }
    void printstack(){
        printf("Current holding track: ");
        for(int i=0;i<top;i++){
            printf("%d ",stack[i]);
        }
        printf("%d\n",stack[top]);
    }

%}

%union {
    int intval;
}

%token <intval> NUM
%start program




%%

program: stmts;

stmts: stmts stmt | stmt;

stmt: NUM{
    ipt[iptid++] = $1;
    if(maxval<$1) maxval=$1;
    iptleg++;
}

%%

int main(){
    int error = yyparse();
    int od[maxval];
    int odid = maxval;
    for(int i=0;i<maxval;i++){
        od[i] = i+1; 
    }
    int now4o = 0;
    int now4i = 0;
    int flag =0;
    /* printf("%d\n",odid); */
    /* printf("%d\n",od[4]);
    printf("%d\n",maxval); */
    while(now4o<odid){
        /* printf("%d,%d\n", od[now4o], ipt[now4i]); */
        if(od[now4o] == ipt[now4i]){
            pass(od[now4o]);
            now4o++;now4i++;
        }
        else if(top>=0 && now4i<=iptleg && stack[top] == ipt[now4i]){
            int tmp = pop();
            printf("Moving train %d from holding track\n",tmp);
            now4i++;
        }
        else{
            push(od[now4o]);
            printf("Push train %d to holding track\n", od[now4o]);
            printstack();
            now4o++;
        }
    }
    while(now4i<iptleg && top>-1){
        int popout = pop();
        if(ipt[now4i] == popout){
            printf("Moving train %d from holding track\n",popout);
            now4i++;
        }
        else{
            printf("Error: Impossible to rearrange\n");
            printf("The first train in the holding track is train %d instead of train %d", popout, ipt[now4i]);
            return 0;
        }
    }
    if(now4i==iptleg && top>=0){
        printf("Error: There is still existing trains in the holding track");
        return 0;
    }
    if(now4i<iptleg && top<0){
        printf("Error: Impossible to rearrange\n");
        printf("There is no any train in the holding track");
        return 0;
    }
    printf("Success");
    

    return 0;
}