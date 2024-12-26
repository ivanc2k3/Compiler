%option noyywrap

%{
    #include "24b.tab.h"
    // extern int yylval;
%}

%%

[1-9][0-9]* {
    yylval.intval = atoi(yytext);
    return NUM;
}
[0] {

}





[ \t\s] {}
\n {}
. {}



%%