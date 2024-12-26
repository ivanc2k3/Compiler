%option noyywrap

%{
    #include "21a.tab.h"
    // extern int yylval;
%}

%%

[0-9]+ {
    yylval.intval = atoi(yytext);
    return NUM;
}


"push" {
    return PUSH;
}

"inverse" {
    return INV;
}

"dec" {
    return DEC;
}

"inc" {
    return INC;
}
"$" {
    
}


[ \t\s] {}
\n {}
. {}



%%