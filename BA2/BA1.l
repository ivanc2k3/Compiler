%{
# include <iostream>
using namespace std;
%}

INTEGER     ^[0-9]+/\r?\n?
FLOAT       ^[0-9]+"."[0-9]+/\r?\n?
string1     ^"\""[^\"\n]*"\""/\r?\n?
string2     ^"\'"[^\'\n]*"\'"/\r?\n?
BOOL        ^(true|false)/\r?\n?
OPERATION   ^[0-9][0-9]*(("+"|"-"|"*"|"/")[0-9]*)+/\r?\n?
ot          ^[^\n]+/\r?\n?

%%

{INTEGER}                     { cout << yytext << " INTEGER" << endl; }
{FLOAT}                     { cout << yytext << " FLOAT" << endl; }
{string1}                     { cout << yytext << " STRING" << endl; }
{string2}                     { cout << yytext << " STRING" << endl; }
{BOOL}                     { cout << yytext << " BOOLEAN" << endl; }
{OPERATION}                     { cout << yytext << " OPERATION" << endl; }
{ot}                        {cout << yytext << " INVALID" << endl;}


\n  {}


%%

int main() {
    yylex();
    return 0;
}
