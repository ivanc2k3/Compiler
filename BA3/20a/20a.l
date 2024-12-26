%option noyywrap

%{
    #include "20a.tab.h"
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

"div" {
    return DIV;
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

"copy" {
    return COPY;
}

"delete" {
    return DELETE;
}

"switch" {
    return SWITCH;
}
[ \t\s] {}
\n {}
. {}



%%