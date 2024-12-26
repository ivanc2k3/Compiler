%{
# include <iostream>
using namespace std;
int bn = 0;
int at = 0;
int pub = 0;
int is = 0;
int count = 0;
%}

bookname1    [A-Z]{1}[a-z]*
bookname2    ([A-Z]{1}[a-z]*_)+[A-Z][a-z]*
author       [A-Z]+", "[A-Z][a-z]+-[A-Z][a-z]+
publication  ([0-9]{4}"/"(01|03|05|07|08|10|12)"/"([0][1-9]|[12][0-9]|3[01])|[0-9]{4}"/02/"([0][1-9]|[12][0-9])|[0-9]{4}"/"(04|04|06|09|11)"/"([0][1-9]|[12][0-9]|30))
isbn         "978-"[0-9]"-"[0-9]{6}"-"[0-9]{2}"-"[0-9]

%%

{bookname1}               { 
    if(count == 0){
        cout << "Book name:" << yytext << endl; 
        count = 1;
    }
}
{bookname2}               { 
    if(count <= 1){
        cout << "Book name:" << yytext << endl; 
        count = 2;
    }
}
{author}               { 
    if(count <= 2){
        cout << "Author:" << yytext << endl; 
        count = 3;
    }
}
{publication}               { 
    if(count <= 3){
        cout << "Publication date:" << yytext << endl; 
        count = 4;
    }
}
{isbn}               { 
    if(count <= 4){
        cout << "ISBN:" << yytext << endl; 
    }
    count = 0;
}

\n                        {}
.                         {}

%%

int main() {
    yylex();
    return 0;
}
