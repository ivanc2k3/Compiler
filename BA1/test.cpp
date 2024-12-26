#include <iostream>
#include <vector>
#include <regex>
#include <stdexcept>
#define fastio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
using namespace std;

enum TokenType {
    ID,
    STRLIT,
    LBR,
    RBR,
    DOT,
    Eof,
};

struct Token {
    Token(TokenType _type, string _value) : type(_type), value(_value) {}
    TokenType type;
    string value;
};

string printTokenType(TokenType type);

bool regex_match1(string s){
    if(!(('A'<=s[0] && s[0]<='Z')||('a'<=s[0] && s[0]<='z')||(s[0]=='_'))) return false;
    for(char c:s){
        if(!(('A'<=c && c<='Z')||('a'<=c && c<='z')||('0'<=c && c<='9')||(c=='_'))) return false;
    }
    return true;
}

bool regex_match2(string s){
    if(!(s.front()=='\"' && s.back()=='\"')) return false;
    long long len = s.length();
    for(int i=1;i<len-1;i++){
        if(s[i]=='\"') return false;
    }
    return true;
}

class Scanner {
public:
    
    vector<Token> tokens;
    
    void scan() {

        string input;
        
        bool allow_all = false;

        while(getline(cin,input)) {
            string tmp;
            for(char word: input) {
                if (!allow_all && word == ' '){
                    if(!tmp.empty())  processtokens(tmp);
                    else continue;
                } else if (word == '\"'){ //STRLIT
                    if(allow_all){
                        tmp += '\"';
                        processtokens(tmp);
                    } else{
                        if(!tmp.empty()) processtokens(tmp);
                        tmp += '\"';
                    }
                    allow_all = !allow_all;
                    
                } else if(!allow_all && word == '(') { //LBR
                    if(!tmp.empty()) processtokens(tmp);
                    tokens.emplace_back(TokenType::LBR, string(1,word));
                } else if(!allow_all && word == ')') { //RBR    
                    if(!tmp.empty()) processtokens(tmp);
                    tokens.emplace_back(TokenType::RBR, string(1,word));
                } else if(!allow_all && word == '.') { //DOT
                    if(!tmp.empty()) processtokens(tmp);
                    tokens.emplace_back(TokenType::DOT, string(1,word));
                } else {
                    tmp += word ;
                }
            }
            if(!tmp.empty()) processtokens(tmp);
        }
        tokens.emplace_back(TokenType::Eof, "EOF");
    }

private:

    void processtokens(string &tmp) {
        regex ID("[A-Za-z_][A-Za-z0-9_]*");
        regex STRLIT("\"[^\"]*\"");
        if(regex_match1(tmp)){
            tokens.emplace_back(TokenType::ID, tmp);
        } else if(regex_match2(tmp)){
            tokens.emplace_back(TokenType::STRLIT, tmp);
        } else{
            throw invalid_argument("Invalid token" + tmp);
        }
        tmp.clear();
    }

};

class Parser {
public:
    Parser(const vector<Token>& _tokens) : tokens(_tokens), currentIndex(0) {}
    
    void stmts() {
        while (currentToken().type != Eof) {
            stmt();
        }
    }
private:
    vector<Token> tokens;
    size_t currentIndex;

    Token currentToken() {
        return currentIndex < tokens.size() ? tokens[currentIndex] : Token(TokenType::Eof, "EOF"); 
    }
    void advance() {
        currentIndex++;
    }

    void expect(TokenType expectedType) {
        if (currentToken().type == expectedType) {
            advance();
        } else {
            throw runtime_error("Syntax error: Expected token type " + printTokenType(expectedType) + ", but got " + printTokenType(currentToken().type));
        }
    }

    void stmt() {
        if (currentToken().type == ID) {
            primary(); 
        } else if (currentToken().type == STRLIT) {
            advance();
        // } else if (currentToken().type == RBR) {
        //     return;
        } else {
            throw runtime_error("Syntax error: Unexpected token in stmt");
        }
    }
    void primary() {
        if (currentToken().type == ID) {
            advance();
            primary_tail();
        } else {
            throw runtime_error("Syntax error: Expected ID in primary");
        }
    }

    void primary_tail() {
        if (currentToken().type == DOT) {
            advance();
            expect(ID);
            primary_tail();
        } else if (currentToken().type == LBR) {
            advance();
            if (currentToken().type != RBR) stmt();
            expect(RBR);
            primary_tail();
        }
    }
};

string printTokenType(TokenType type) {
    switch (type) {
        case ID: return "ID";
        case STRLIT: return "STRLIT";
        case LBR: return "LBR"; 
        case RBR: return "RBR";
        case DOT: return "DOT";
        case Eof: return "EOF";
        default: return "Unknown";
    }
}

int main() {
    Scanner scanner;
    try {
        scanner.scan();
    } catch (const invalid_argument &e) {
        cerr << "Scanner" << endl;
        cout << "invalid input" << endl;
        // cout << e.what() << endl;
        return 0;
    }

    try {
        Parser parser(scanner.tokens);
        parser.stmts();
    } catch (const runtime_error &e) {
        cerr << "Parser" << endl;
        cout << "invalid input" << endl;
        // cout << e.what() << endl;
        return 0;
    }

    for (const auto& token : scanner.tokens) {
        if (token.type == TokenType::Eof) break;
        cout << printTokenType(token.type) << " " << token.value << endl;
    }

    return 0;
}
