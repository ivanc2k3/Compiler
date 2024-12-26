%option noyywrap
%{
    #include <iostream>
    #include <string>
    using namespace std;
    int counter = 0;
    int counttab = 0;
    void print_tabs(){
        for(int i=0;i<counter;i++) cout<<'\t';
    }
%}

NEXTLINE (\n|\r|\r\n)
TAB [\t]+
SPACE [ ]
ANY [^\s]
NOTAB ^[^\t]


MI \#
THREE_QUATE \"\"\"
PRINT   print\(
RIGHTBRACE  \)
IF "if "("True"|"False")":"


%x LINE_ANNOTATION
%x LINES_ANNOTATION
%x PRINT_STATEMENT
%x IF_STATEMENT

%%
{MI}{SPACE} {
    if(counter!=counttab) {
        for(int i=0;i<counter-1;i++) cout << '\t';
        cout << "}\n";counter--;counttab=0;
    }
    cout<<"// ";
    BEGIN LINE_ANNOTATION;
}
<LINE_ANNOTATION>{NEXTLINE} {
    cout<<endl;
    if(counter>0)counttab=0;
    BEGIN INITIAL;
}
<LINE_ANNOTATION>. {
    cout<<yytext;
}


{THREE_QUATE} {
    if(counter!=counttab) {
        for(int i=0;i<counter-1;i++) cout << '\t';
        cout << "}\n";counter--;counttab=0;
    }
    cout<<"/*";
    if(counter>0)counttab=0;
    BEGIN LINES_ANNOTATION;
}
<LINES_ANNOTATION>{THREE_QUATE}{NEXTLINE} {
    cout<<"*/"<<endl;
    if(counter>0)counttab=0;
    BEGIN INITIAL;
}
<LINES_ANNOTATION>.|{NEXTLINE} {
    cout<<yytext;
    if(counter>0)counttab=0;
}

{PRINT} {
    if(counter!=counttab) {
        for(int i=0;i<counter-1;i++) cout << '\t';
        cout << "}\n";counter--;counttab=0;
    }
    cout<<"cout << ";
    BEGIN PRINT_STATEMENT;
}
<PRINT_STATEMENT>{RIGHTBRACE}{NEXTLINE}? {
    cout<<" << endl;"<<endl;
    if(counter>0)counttab=0;
    BEGIN INITIAL;
}
<PRINT_STATEMENT>. {
    cout<<yytext;
}


{IF}{NEXTLINE} {
    cout<<"if("<<(yytext[3]=='T'?"true)":"false)")<<" {"<<endl;
    counter++;
    counttab =0;
}
\t   {
    cout<<yytext;
    counttab++;
}


\n {cout<<endl;}
\r {cout<<"\r";}
\t {}
. {}

%%
int main(int argc, char *argv[]){
    yylex();
    return 0;
}