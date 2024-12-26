%option noyywrap

%{
    #include "22a.tab.h"
    // extern int yylval;
%}

%%

[0-9]+ {
    yylval.intval = atoi(yytext);
    return NUM;
}


"+" {
    return ADD;
}

"-" {
    return SUB;
}

[Pp] {
    return PER;
}

[Cc] {
    return COM;
}


[ \t\s] {}
\n {}
. {}



%%