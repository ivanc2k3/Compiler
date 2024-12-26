%option noyywrap

%{
    #include "20b.tab.h"
    // extern int yylval;
%}

%%

([0-9]*[.])?[0-9]+|[0-9]+[.][0-9]* {
    yylval.intval = atof(yytext);
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
. {}



%%