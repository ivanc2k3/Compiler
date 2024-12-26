%option noyywrap

%{
	#include "hw3b.tab.h"
	int location = 0;
%}

%%

"[" {
    location += yyleng;
    return LBR;
}
"]" {
    location += yyleng;
    return RBR;
}
"(" {
    location += yyleng;
    return LPR;
}
")" {
    location += yyleng;
    return RPR;
}
"^T" {
    location += yyleng;
    return TRS;
}
"," {
    location += yyleng;
    return COM;
}
"+" {
    location += yyleng;
    yylval.location = location;
    return ADD;
}
"-" {
    location += yyleng;
    yylval.location = location;
    return SUB;
}
"*" {
    location += yyleng;
    yylval.location = location;
    return MUL;
}
[0-9]+ {
    location += yyleng;
    yylval.num = atoi(yytext);
    return NUM;
}
[ \s\t] {
    location += yyleng;
}
\n {}
. {}





%%