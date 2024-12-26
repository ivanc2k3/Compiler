%option noyywrap
%{
    #include <iostream>
    #include <string>
    using namespace std;
    int counter = 0;
    void print_tabs(){
        for(int i=0;i<counter;i++) cout<<'\t';
    }
%}

NEXTLINE (\n|\r|\r\n)
TAB \t
SPACE [ ]
ANY [^\s]

DOUBLE_SLASH \/\/
SLASH_STAR \/\*
STAR_SLASH \*\/
COUT cout
MOVE_LEFT <<
ENDL endl
IF if\((true|false)\)
BRACE_LEFT \{
BRACE_RIGHT \}


%x LINE_ANNOTATION
%x LINES_ANNOTATION
%x PRINT_STATEMENT
%x IF_STATEMENT

%%
{DOUBLE_SLASH}{SPACE} {
    print_tabs();
    cout<<"# ";
    BEGIN LINE_ANNOTATION;
}
<LINE_ANNOTATION>{NEXTLINE} {
    cout<<endl;
    BEGIN INITIAL;
}
<LINE_ANNOTATION>. {
    cout<<yytext;
}


{SLASH_STAR} {
    print_tabs();
    cout<<"\"\"\"";
    BEGIN LINES_ANNOTATION;
}
<LINES_ANNOTATION>{STAR_SLASH}{NEXTLINE} {
    cout<<"\"\"\""<<endl;
    BEGIN INITIAL;
}
<LINES_ANNOTATION>{ANY}|{NEXTLINE}|\s {
    cout<<yytext;
}

{COUT}{SPACE}{MOVE_LEFT}{SPACE} {
    print_tabs();
    cout<<"print(";
    BEGIN PRINT_STATEMENT;
}
<PRINT_STATEMENT>{SPACE}{MOVE_LEFT}{SPACE}{ENDL}";"{NEXTLINE}? {
    cout<<")"<<endl;
    BEGIN INITIAL;
}
<PRINT_STATEMENT>. {
    cout<<yytext;
}


{IF}{SPACE}{BRACE_LEFT}{NEXTLINE} {
    print_tabs();
    cout<<"if "<<(yytext[3]=='t'?"True":"False")<<":"<<endl;
    counter++;
}
{BRACE_RIGHT}{NEXTLINE} {
    counter--;
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