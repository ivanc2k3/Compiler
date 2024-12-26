%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
int indent = 0;
void print_tabs() {
    for(int i = 0; i < indent; i++) {
        printf("\t");
    }
}
%}
LF            \r?\n?
TAB            \t
SPACE        [ ]
ANY         [^\t]

DSLASH        \/\/
SLASHSTAR    \/\*
STARSLASH    \*\/

COUT        cout
STREAMIN    \<\<
ENDL        endl
SEMICOLON    ;

POSINT        [0-9]|[1-9][0-9]*
DQUOTE        \"
STRING        {DQUOTE}.+{DQUOTE}

BOOL        true|false
IF            if
LBRACK        \(
RBRACK        \)
LBRACE        \{
RBRACE        \}

%x SCOMMENT
%x MCOMMENT
%x OUTPUT
%x IF_COND
%%
{DSLASH}{SPACE}            {
    BEGIN SCOMMENT;
}
<SCOMMENT>.+ {
    print_tabs();
    printf("# %s\n", yytext);
}
<SCOMMENT>{LF}            {
    BEGIN INITIAL;
}

{SLASHSTAR}{LF}                {
    BEGIN MCOMMENT;
    print_tabs();
    printf("%s", "\"\"\"\n");
}
<MCOMMENT>.+|\n {
    print_tabs();
    printf("%s", yytext);
}
<MCOMMENT>{STARSLASH}{LF}    {
    print_tabs();
    printf("%s", "\"\"\"\n");
    BEGIN INITIAL;
}

{COUT}{SPACE}{STREAMIN}{SPACE}                {
    BEGIN OUTPUT;
}
<OUTPUT>{POSINT}                            {
    print_tabs();
    printf("print(%s)\n", yytext);
}
<OUTPUT>{STRING}                            {
    print_tabs();
    printf("print(%s)\n", yytext);
}
<OUTPUT>{SPACE}{STREAMIN}{SPACE}{ENDL}{SEMICOLON}{LF}    {
    BEGIN INITIAL;
}

{IF}{LBRACK}                        {
    BEGIN IF_COND;
}
<IF_COND>{BOOL}                        {
    if(strcmp(yytext, "true") == 0) {
        print_tabs();
        printf("if True:\n");
    }else if(strcmp(yytext, "false") == 0) {
        print_tabs();
        printf("if False:\n");
    }
}
<IF_COND>{RBRACK}{SPACE}{LBRACE}{LF} {
    indent++;
    BEGIN INITIAL;
}

{RBRACE}{LF}                                {
    indent--;
}


<<EOF>>            { return 0; }
.|\n            {}
%%
int main(void) {
    yylex();
    return 0;
}