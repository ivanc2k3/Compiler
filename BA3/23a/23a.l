%option noyywrap

%{
	#include "23a.tab.h"
%}

rn ([0-9]*[.])?[0-9]+|[0-9]+[.][0-9]*

%%

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
{rn} {
    yylval.num = atof(yytext);
    // printf(yytext);
    return NUM;
}
[ \s\t\n] {}
"\r\n" {}
. {
    fprintf(stderr, "Invalid Value");
    exit(0);
}





%%