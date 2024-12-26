%{
# include <iostream>
using namespace std;
%}

variable    [A-Za-z_][A-Za-z0-9_]*
fn1         ^[A-Za-z_][A-Za-z0-9_]*"("([A-Za-z_][A-Za-z0-9_]*)?")"/\r?\n
fn2         ^[A-Za-z_][A-Za-z0-9_]*\(([A-Za-z_][A-Za-z0-9_]*)(", "[A-Za-z_][A-Za-z0-9_]*)*\)/\r?\n



%%

{fn1}               { cout << yytext << endl; }
{fn2}               { cout << yytext << endl; }



\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
