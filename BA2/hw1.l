%{
int tabs=0;
void print_tab(){
    for( int i = 0 ; i< tabs; i++)
        printf("\t");
}
%}
word    [^{}\t\n]+
wordl   [^{}\t\n]+"{"
wordlr  "{"[^{}\t\n]+
wordr   "}"[^{}\t\n]+
%%
"{"         {print_tab(); printf("{"); tabs++;}
"}"         {tabs--; print_tab(); printf("}");}
{wordl}     {print_tab(); printf("%s",yytext); tabs++;}
{wordr}     {tabs--; print_tab(); ECHO;}
{wordlr}    {print_tab(); ECHO; tabs++;}
{word}      {print_tab(); ECHO;}
%%
int main(int argc, char *argv[]) {
    yylex();
    return(0);
}