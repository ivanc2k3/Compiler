#include<iostream>
#include<vector>
#include<map>
using namespace std;

bool isIDchar(char c) {
    if(c == '_')
        return 1;
    if(c >= 'A' and c <= 'Z')
        return 1;
    if(c >= 'a' and c <= 'z')
        return 1;
    if(c >= '0' and c <= '9')
        return 1;
    return 0;
}

struct token{
    int type;
    string content;
    token(int t, string c) : type(t), content(c) {}
};

vector<token> vec;
int idx;
int next_type;
bool flag;
map<int, string> tokenName = {
    {0, "ID"},
    {1, "STRLIT"},
    {2, "LBR"},
    {3, "RBR"},
    {4, "DOT"},
    {9, "END"}
};

void scanner(string input) {
    // cout << input << endl;
    int len = input.size();
    for(int i=0;i<len;i++) {
        char c = input[i];
        if(c == ' ')
            continue;
        if((c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z') or c == '_') {     //ID case
            int j;
            string str = "";
            for(j=i;j<len;j++) {
                if(isIDchar(input[j]))
                    str += input[j];
                else if(input[j] == ' ' or input[j] == '.' or input[j] == '(' or input[j] == ')' or input[j] == '\n') {
                    i = j-1;
                    break;
                }else {
                    // cout << "bad ID" << endl;
                    // cout << input[j] << endl;
                    flag = 0;
                    break;
                }
            }
            if(!flag)
                return;
            if(j == len)
                i = j;
            token t(0, str);
            vec.push_back(t);
        }
        else if(c == '"') {
            int j;
            string str = "";
            str += '"';
            for(j=i+1;j<len;j++) {
                if(input[j] != '"')
                    str += input[j];
                else {
                    str += '"';
                    break;
                }
            }
            i = j;
            if(str[int(str.size())-1] != '"') {
                flag = 0;
                return;
            }
            token t(1, str);
            vec.push_back(t);
        }
        else if(c == '(') {
            token t(2, "(");
            vec.push_back(t);
        }
        else if(c == ')') {
            token t(3, ")");
            vec.push_back(t);
        }
        else if(c == '.') {
            token t(4, ".");
            vec.push_back(t);
        }
    }
}

bool stmt();

void terminal() {
    idx++;
    next_type = vec[idx+1].type;
    return;
}

bool primary_tail() {
    // cout << "primary_tail" << endl;
    if(next_type == 4) {
        // cout << "DOT" << endl;
        terminal();
        if(next_type == 0) {
            // cout << "ID" << endl;
            terminal();
            return primary_tail();
        }
        return 0;
    }
    else if(next_type == 2) {
        // cout << "LBR" << endl;
        terminal();
        if(!stmt())
            return 0;
        if(next_type == 3) {
            // cout << "RBR" << endl;
            terminal();
            return primary_tail();
        }
        return 0;
    }
    return 1;
}

bool primary() {
    // cout << "primary" << endl;
    if(next_type == 0) {
        // cout << "ID" << endl;
        terminal();
        // cout << "--debug-- " << next_type << endl;
        return primary_tail();
    }
    return 0;
}

bool stmt() {
    // cout << "stmt" << endl;
    if(next_type == 1) {
        // cout << "STRLIT" << endl;
        terminal();
        return 1;
    }
    if(next_type == 0) 
        return primary();
    return 1;
}

bool stmts() {
    // cout << "stmts" << endl;
    if(next_type != 9) {
        return stmt() && stmts();
    }
    else 
        return 1;
}

bool program() {
    // cout << "program" << endl;
    return stmts();
}

int main() {
    string input, line;
    flag = 1;
    while(getline(cin, line)) {
        // if(line == "9")
        //     break;
        input += line + "\n";
    }
    scanner(input);
    if(!flag) {
            cout << "invalid input" << endl;
            return 0;
    }
    token last(9,"$");
    vec.push_back(last);
    next_type = vec[0].type;
    idx = -1;
    // for(auto iter:vec) {
    //     if(iter.type != 9)
    //         cout << tokenName[iter.type] << ' ' << iter.content << endl;
    // }
    if(program()) {
        for(auto iter:vec) {
            if(iter.type != 9)
                cout << tokenName[iter.type] << ' ' << iter.content << endl;
        }
    }
    else    
        cout << "invalid input" << endl;
    return 0;
}