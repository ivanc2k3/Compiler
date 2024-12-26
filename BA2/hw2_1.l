%{
# include <iostream>
using namespace std;
int count = 0;
void printTab(){
    for(int i=0;i<count;i++){
        cout << '\t';
    }
}
%}
lb  [^\n{}]+"{"[^\n{}]*$
nb  [^\n{}]+
hlb "{"[^\n{}]+
hrb "}"[^\n{}]+
rb  [^\n{}]+"}"[^\n{}]*$
%%
"{"     {printTab(); ECHO; count++;}
"}"     {count--; printTab(); ECHO;}
{lb}    {printTab(); ECHO; count++;}
{nb}    {printTab(); ECHO;}
{hlb}   {printTab(); ECHO; count++;}
{hrb}   {count--; printTab(); ECHO;}
{rb}    {printTab(); ECHO; count--;}
\n  {}

%%
int main(){
    yylex();
    return 0;
}