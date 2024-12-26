# include <iostream>
# include <vector>
# include <set>
using namespace std;

vector<pair<string, string>> tks;

bool isFNum(char c) {
    if(c >= '1' and c <= '9')
        return 1;
    return 0;
}
bool isNum(char c) {
    if(c >= '0' and c <= '9')
        return 1;
    return 0;
}

bool isID(char c) {
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

bool isFID(char c) {
    if(c >= 'A' and c <= 'Z')
        return 1;
    if(c >= 'a' and c <= 'z')
        return 1;
    return 0;
}

bool isSymbol(char c){
    set<char> v = {'+', '-', '*', '/', '=', '(', ')', '{', '}', '<', '>', ';'};
    if(v.count(c)) return 1;
    else return 0;
}

bool isKeyword(string s){
    set<string> st = {"if", "while"};
    if(st.count(s)) return 1;
    else return 0;
}

signed main(){
    string s;

    while(cin >> s){
        pair<string, string> tmp;

        for(int i = 0;i < s.length();i++){
            if(s[i] == '0' && tmp.first == "" && tmp.second == ""){
                tks.push_back({"NUM", "0"});
                continue;
            }
            if(tmp.second != ""){
                if(isKeyword(tmp.second)){
                    tks.push_back({"KEYWORD", tmp.second});
                    tmp.first = ""; tmp.second = "";
                }
                else if(tmp.first == "NUM" && !isNum(s[i])){
                    tks.push_back({tmp.first, tmp.second});
                    tmp.first = ""; tmp.second = "";
                    // tks.push_back({"Invalid",""});
                }
                else if(tmp.first == "IDENTIFIER" && !isID(s[i])){
                    tks.push_back({tmp.first, tmp.second});
                    tmp.first = ""; tmp.second = "";
                    // tks.push_back({"Invalid",""});
                }
            }
            tmp.second += s[i];
            if(isSymbol(s[i])){
                tks.push_back({"SYMBOL", tmp.second});
                tmp.second = "";continue;
            }
            else if(tmp.second.length() == 1){
                if(isFNum(s[i])){
                    tmp.first = "NUM";
                }
                else if(isFID(s[i])){
                    tmp.first = "IDENTIFIER";
                }
            }
            if(tmp.first == "" && tmp.second != ""){
                tmp.second = "";
                tks.push_back({"Invalid",""});
            }
            
        }
        if(tmp.second != ""){
            if(isKeyword(tmp.second)){
                tks.push_back({"KEYWORD", tmp.second});
                tmp.first = ""; tmp.second = "";
            }
            else if(tmp.first != ""){
                tks.push_back({tmp.first, tmp.second});
                tmp.first = ""; tmp.second = "";
            }
        }
    }

    for(int i=0;i<tks.size();i++){
        if(tks[i].first == "Invalid") cout << "Invalid" << '\n';
        else cout << tks[i].first << " \"" << tks[i].second << '\"' <<'\n';
    }


    return 0;
}