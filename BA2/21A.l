%{
# include <iostream>
# include <string>
using namespace std;
%}

flt         ^[0-9]*\.[0-9]*/\r?\n
rn          ^[0-9]+[\.]?[0-9]*[Ee][+|-]?[0-9]+/\r?\n

%%

{flt}                     { cout << yytext << endl; }
{rn}                     { cout << yytext << endl; }


\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
