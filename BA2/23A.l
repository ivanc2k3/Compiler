%{
# include <iostream>
using namespace std;
%}

num         ^[1-9]+[0-9]*/\r?\n
float       ^[0-9]*.[0-9]+/\r?\n
string1     ^"\""[^\"\n]*"\""/\r?\n
string2     ^"\'"[^\'\n]*"\'"/\r?\n
variable    ^[A-Za-z_]+[A-Za-z_0-9]*/\r?\n

%%

{num}                     { cout << yytext << " INTEGER" << endl; }
{float}                   { cout << yytext << " FLOAT" << endl; }
{string1}                 { cout << yytext << " STRING" << endl; }
{string2}                 { cout << yytext << " STRING" << endl; }
{variable}                { cout << yytext << " VARIABLE" << endl; }
\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
