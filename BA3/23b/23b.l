%option noyywrap

%{
    #include "23b.tab.h"
    // extern int yylval;
%}

%%

0|[1-9][0-9]*|[-][1-9][0-9]* {
    yylval.intval = atoi(yytext);
    return NUM;
}

"+" {
    return ADD;
}

"-" {
    return SUB;
}

"*" {
    return MUL;
}

"/" {
    return DIV;
}

[ \t\s] {}
\n {}
"\r\n" {}
. {}



%%