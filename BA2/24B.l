%{
    #include <iostream>
    #include <string>
    using namespace std;
    int tabcnt = 0;
    int beforetabs = 0;
    void print_tabs(){
        for(int i=0;i<tabcnt;i++){
            cout<<"\t";
        }
    }

    void doBRA(){
        while(beforetabs<tabcnt){
            tabcnt--;
            print_tabs();
            cout<<"}\n";
        }
    }
%}

NL (\n|\r|\r\n)
TB \t
SC [ ]
OTHER [^\s]
SHARP #
TRIPPF \"\"\"
TRIPPS \"\"\"
PRINTP "print\("
RBR "\)"

%x ONLINE
%x TOLINE
%x PSFIVE

%%
{SHARP}{SC} {doBRA();print_tabs();cout<<"// ";beforetabs=0;BEGIN ONLINE;}
<ONLINE>{NL} {cout<<endl;beforetabs=0;BEGIN INITIAL;}
<ONLINE>{OTHER} {cout<<yytext;beforetabs=0;}
{TRIPPF} {doBRA();print_tabs();cout<<"/*";beforetabs=0;BEGIN TOLINE;}
<TOLINE>{TRIPPS}{NL} {cout<<"*/"<<endl;beforetabs=0;BEGIN INITIAL;}
<TOLINE>{OTHER}|{NL}|\s {cout<<yytext;beforetabs=0;}
{PRINTP} {doBRA();print_tabs();cout<<"cout << ";beforetabs=0;BEGIN PSFIVE;}
<PSFIVE>{RBR}{NL}? {cout<<" << endl;"<<endl;beforetabs=0;BEGIN INITIAL;}
<PSFIVE>{OTHER} {cout<<yytext;beforetabs=0;}
("if True\:"){NL}|("if False\:"){NL} {doBRA();print_tabs();tabcnt++;cout<<"if"<<(yytext[3]=='F'?"(false)":"(true)")<<" {"<<endl;beforetabs=0;}
\t {beforetabs++;}
\r {cout<<"\r";}
\n {doBRA();beforetabs=0;cout<<endl;}
. {}

%%
int main(int argc, char *argv[]){
    yylex();
    return 0;
}