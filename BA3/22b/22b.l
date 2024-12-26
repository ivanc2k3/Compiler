%option noyywrap

%{
	#include "22b.tab.h"
%}


%%

"<and>" {
    return AND1;
}
"</and>" {
    return AND2;
}
"<or>" {
    return OR1;
}
"</or>" {
    return OR2;
}
"<not>" {
    return NOT1;
}
"</not>" {
    return NOT2;
}
"<true/>" {
    yylval.num = 1;
    // printf(yytext);
    return NUM;
}
"<false/>" {
    yylval.num = 0;
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