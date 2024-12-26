%option noyywrap

%{
	#include "24a.tab.h"
%}

rn [-]?([0-9]*[.])?[0-9]+|[-]?[0-9]+[.][0-9]*

%%

"h" {
    return H;
}
"f" {
    return F;
}
"g" {
    return G;
}
"(" {
    return LPR;
}
")" {
    return RPR;
}
"," {
    return COM;
}
{rn} {
    yylval.num = atof(yytext);
    // printf(yytext);
    return NUM;
}
[ \s\t\n] {}
"\r\n" {}
. {
    
}





%%