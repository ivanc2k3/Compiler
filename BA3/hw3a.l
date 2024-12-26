%option noyywrap

%{
    #include "hw3a.tab.h"
    // extern int yylval;
%}

%%

[0-9]+ {
    yylval.intval = atoi(yytext);
    return NUM;
}


"load" {
    return LOAD;
}

"add" {
    return ADD;
}

"sub" {
    return SUB;
}

"mul" {
    return MUL;
}

"mod" {
    return MOD;
}

"inc" {
    return INC;
}

"dec" {
    return DEC;
}
[\t] {}
\n {}
. {}



%%