%option noyywrap

%{
    #include "19b.tab.h"
    // extern int yylval;
%}

%%

[0-9]+ {
    yylval.intval = atof(yytext);
    return NUM;
}


"^" {
    return HAT;
}

"+" {
    return ADD;
}

"-" {
    return SUB;
}

"{" {
    return LBR;
}

"}" {
    return RBR;
}

"\\frac" {
    return FRAC;
}

[ \t\s] {}
\n {}
. {return NOP;}



%%