%{
	#include <stdio.h>
	#include <string>
    #include <iostream>
    #include <algorithm>
    void print_no_nl(char* yytext)
    {
       // remove newline
	   std::string s(yytext);
	   s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	   std::cout << s;

    }
%}

%option noyywrap

INTEGER ^[1-9]?[0-9]+\n
FLOAT	^[1-9]?([0-9]*[\.][0-9]+|[0-9]+[\.][0-9]*)\n
STRING 	(\"[^"]+\"\n)|('[^']+'\n)
BOOL     ^(true|false)\n
OPERATION   ^[0-9][0-9]*("+"|"-"|"*"|"/")+[0-9]*\n
ot          ^[^\n]+\n

%%

{INTEGER} {print_no_nl(yytext); printf(" INTERGER\n");}
{FLOAT} {print_no_nl(yytext); printf(" FLOAT\n");}
{STRING} {print_no_nl(yytext); printf(" STRING\n");}
{BOOL} {print_no_nl(yytext); printf(" BOOLEAN\n");}
{OPERATION} {print_no_nl(yytext); printf(" OPERATION\n");}
{ot} {print_no_nl(yytext); printf(" INVALID\n");}


.|\n {}

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}