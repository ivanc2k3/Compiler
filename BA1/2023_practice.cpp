#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

enum TokenType {
    ID,
    NATIONNUM,
    PHONENUM,
    YEAR,
    MONTH,
    DAY,
    PLUS,
    DOT,
    LBR,
    RBR,
    SLASH,
    Eof,
};

struct Token {
    Token(TokenType _type, string _value) : type(_type), value(_value) {}
    TokenType type;
    string value;
};

string printTokenType(TokenType type);


bool regex_match_ID(string s){
    if( 'A'<=s.front() && s.front()<='Z' ) return false;
    long long len = s.length();
    if(len != 10) return false;
    for(int i=1;i<len;i++){
        if( !('0'<=s.at(i) && s.at(i)<='9') ) return false;
    }
    return true;
}

bool regex_match_NATIONNUM(string s){
    long long len = s.length();
    if(len != 3) return false;
    for(int i=0;i<len;i++){
        if( !('0'<=s.at(i) && s.at(i)<='9') ) return false;
    }
    return true;
}

bool regex_match_PHONENUM(string s){
    if( !(s.front()=='9') ) return false;
    long long len = s.length();
    if(len != 9) return false;
    for(int i=1;i<len;i++){
        if( !('0'<=s.at(i) && s.at(i)<='9') ) return false;
    }
    return true;
}

bool regex_match_YEAR(string s){
    if( !(s.front()!='1' || s.front()!='2') ) return false;
    long long len = s.length();
    if(len != 4) return false;
    for(int i=1;i<len;i++){
        if( !('0'<=s.at(i) && s.at(i)<='9') ) return false;
    }
    return true;
}

bool regex_match_MONTH(string s){
    unordered_set<string> months = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    return months.find(s) != months.end();
}

bool regex_match_DAY(string s){
    long long len = s.length();
    if(len == 1){
        if('1'<=s.front() && s.front()<='9') return true;
    } else if(len == 2){
        if(s.front()=='1' || s.front()=='2'){
            if('0'<=s.back() && s.back()<='9') return true;
        } else if(s.front()=='3'){
            if(s.back()=='1' || s.back()=='2') return true;
        }
    }
    return false;
}

class Scanner {
public:
    
    vector<Token> tokens;
    
    void scan() {
        string input,tmp;
        getline(cin,input);
        for(char word: input){
            if(word == ' '){
                if(!tmp.empty()) processtokens(tmp);
            } else if(word == '+'){
                if(!tmp.empty()) processtokens(tmp);
                tokens.emplace_back(TokenType::PLUS, "+");
            } else if(word == '.'){
                if(!tmp.empty()) processtokens(tmp);
                tokens.emplace_back(TokenType::DOT, ".");
            } else if(word == '('){
                if(!tmp.empty()) processtokens(tmp);
                tokens.emplace_back(TokenType::LBR, "(");
            } else if(word == ')'){
                if(!tmp.empty()) processtokens(tmp);
                tokens.emplace_back(TokenType::RBR, ")");
            } else if(word == '/'){
                if(!tmp.empty()) processtokens(tmp);
                tokens.emplace_back(TokenType::SLASH, "/");
            } else{
                tmp += word;
            }
        }
        if(!tmp.empty()) processtokens(tmp);
        tokens.emplace_back(TokenType::Eof, "EOF");
    }

private:

    void processtokens(string &tmp) {
        // cerr << tmp <<endl;
        if(regex_match_ID(tmp)){
            tokens.emplace_back(TokenType::ID, tmp);
        } else if(regex_match_NATIONNUM(tmp)){
            tokens.emplace_back(TokenType::NATIONNUM, tmp);
        } else if(regex_match_PHONENUM(tmp)){
            tokens.emplace_back(TokenType::PHONENUM, tmp);
        } else if(regex_match_YEAR(tmp)){
            tokens.emplace_back(TokenType::YEAR, tmp);
        } else if(regex_match_MONTH(tmp)){
            tokens.emplace_back(TokenType::MONTH, tmp);
        } else if(regex_match_DAY(tmp)){
            tokens.emplace_back(TokenType::DAY, tmp);
        } else{
            cerr << tmp << endl;
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
            return;
        } else if (currentToken().type == PLUS) {
            phone();
        } else if (currentToken().type == MONTH || currentToken().type == YEAR) {
            date();
        } else {
            throw runtime_error("Syntax error: Unexpected token in stmt");
        }
    }
    void phone(){
        expect(PLUS);
        expect(LBR);
        expect(NATIONNUM);
        expect(RBR);
        expect(PHONENUM);
    }
    void date(){
        if(currentToken().type == MONTH){
            expect(MONTH);
            expect(DOT);
            expect(DAY);
            expect(DOT);
            expect(YEAR);
        } else {
            expect(YEAR);
            expect(SLASH);
            expect(MONTH);
            expect(SLASH);
            expect(DAY);
        }
    }
};

string printTokenType(TokenType type) {
    switch (type) {
        case ID: return "ID";
        case NATIONNUM: return "NATIONNUM";
        case PHONENUM: return "PHONENUM"; 
        case YEAR: return "YEAR";
        case MONTH: return "MONTH";
        case DAY: return "DAY";
        case PLUS: return "PLUS";
        case DOT: return "DOT";
        case LBR: return "LBR";
        case RBR: return "RBR";
        case SLASH: return "SLASH";
        case Eof: return "EOF";
        default: return "Unknown";
    }
}

int main(void){
    Scanner scanner;
    try {
        scanner.scan();
    } catch (const invalid_argument &e) {
        cout << "invalid input" << endl;
        // cout << e.what() << endl;
        return 0;
    }

    try {
        Parser parser(scanner.tokens);
        parser.stmts();
    } catch (const runtime_error &e) {
        cout << "invalid input" << endl;
        // cout << e.what() << endl;
        return 0;
    }

    for (const auto& token : scanner.tokens) {
        if (token.type == TokenType::Eof) break;
        cout << token.value << " " << printTokenType(token.type) << endl;
    }

    return 0;
}