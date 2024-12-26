%{
# include <iostream>
using namespace std;
%}

atm         "$"(100000|[1-9]?[0-9]{1,4})
day         \b"+"(0|[1-9][0-9]?|[1-2][0-9]{2}|3[0-5][0-9]|36[0-5])\b
time        ([01][0-9]|[2][0-3])":"([0-5][0-9])
place       [A-Z][a-z\.-]+[A-Z]

%%

{atm}                     { cout << "transfer " << yytext << endl; }
{day}                     { cout << "after " << yytext << "days" << endl; }
{time}                     { cout << "at " << yytext << endl; }
{place}                     { cout << "at " << yytext << endl; }





\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
