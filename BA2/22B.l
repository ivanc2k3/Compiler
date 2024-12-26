%{
# include <iostream>
using namespace std;
int cnt = 0;
bool is_leap_year(int y){ return y%400==0||(y%100!=0&&y%4==0); }
%}

name            [A-Z]+", "[A-Z][a-z]+"-"[A-Z][a-z]+
id              [A-Z][12][0-9]{8}
email           [0-9]+"@"[a-z]+([.][a-z]+)+
bd              ([0-9]{4}"/"(01|03|05|07|08|10|12)"/"([0][1-9]|[12][0-9]|3[01])|[0-9]{4}"/02/"([0][1-9]|[12][0-9])|[0-9]{4}"/"(04|04|06|09|11)"/"([0][1-9]|[12][0-9]|30))
bd2             ([0-9]{2}"/"(01|03|05|07|08|10|12)"/"([0][1-9]|[12][0-9]|3[01])|[0-9]{2}"/02/"([0][1-9]|[12][0-9])|[0-9]{2}"/"(04|04|06|09|11)"/"([0][1-9]|[12][0-9]|30))
phone           "+886"[0-9]{9}

%%

{name}               { 
    
    if(cnt != 0) cout << endl;
    cout << yytext << endl;
    cnt += 1; 
    
}
{id}               { 
    
    cout << "identity number: " << yytext << endl; 
    
}
{email}               { 
    
    cout << "email: " << yytext << endl; 
    
}
{bd}               { 
    
    cout << "birthday: " << yytext << endl; 
    
}
{bd2}               { 
    
    cout << "birthday: " << yytext << endl; 
    
}
{phone}               { 
    
    cout << "phone: " << yytext << endl; 
    
}


\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
