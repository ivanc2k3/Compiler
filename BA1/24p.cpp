# include <iostream>
# include <vector>
# include <string>
# include <map>
# include <algorithm>
# include <set>
using namespace std;

vector<pair<string, string>> tks; // terminal, string
bool check=1;
int cnt = 0;

bool isid(string s){
    if(s.length()<1) return 0;
    if(!((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z' || s[0] == '_'))) return 0;
    for(int i=1;i<s.length();i++){
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'|| s[i] >= '0' and s[i] <= '9' || s[0] == '_'))) return 0;
    }
    return 1;
}

bool isphonenum(string s){
    if(s.length()!=10) return 0;
    if(s[0]!='0') return 0;
    if(s[1]!='9') return 0;
    for(int i=2;i<s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}
bool ispath(string s){
    if(s.length()<1)return 0;
    for(int i=0;i<s.length();i++){
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'|| s[i] >= '0' and s[i] <= '9'))) return 0;
    }
    return 1;
}
bool ismail(string s){
    set<string>st = {"gmail", "yahoo", "iCloud", "outlook"};
    if(st.count(s)) return 1;
    return 0;
}

bool isdomain(string s){
    set<string>st = {"org", "com"};
    if(st.count(s)) return 1;
    return 0;
}

bool isscheme(string s){
    set<string>st = {"https", "tel", "mailto"};
    if(st.count(s)) return 1;
    return 0;
}

bool checkre(string& s){
    if(ismail(s)){
        tks.push_back({"MAILDOMAIN", s});
    }
    else if(isdomain(s)){
        tks.push_back({"DOMAIN", s});
    }
    else if(isscheme(s)){
        tks.push_back({"SCHEME", s});
    }
    else if(isphonenum(s)){
        tks.push_back({"PHONENUM", s});
    }
    else if(ispath(s)){
        tks.push_back({"PATH", s});
    }
    else{
        return 0;
    }
    s.clear();
    return 1;

}

bool scn(){
    string s = "";

    cin >> s;
    string tmp="";
    for(int i=0;i<s.length();i++){
        if(s[i] == ':'){
            if(!tmp.empty()){
                if(!checkre(tmp)) return 0;
            }
            tks.push_back({"COLON", ":"});
        }
        else if(s[i] == '@'){
            if(!tmp.empty()){
                if(!checkre(tmp)) return 0;
            }
            tks.push_back({"AT", "@"});
        }
        else if(s[i] == '.'){
            if(!tmp.empty()){
                if(!checkre(tmp)) return 0;
            }
            tks.push_back({"DOT", "."});
        }
        else if(s[i] == '/'){
            if(!tmp.empty()){
                if(!checkre(tmp)) return 0;
            }
            tks.push_back({"SLASH", "/"});
        }
        else{
            tmp+=s[i];
        }
    }
    if(!tmp.empty()){
        if(!checkre(tmp)) return 0;
    }
    
    return 1;
}


void DOT(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "DOT"){
        check = 0;
        return;
    }
    cnt++;
}

void SLASH(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "SLASH"){
        check = 0;
        return;
    }
    cnt++;
}

void AT(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        check = 0;
        return;
    }
    if(tks[cnt].first != "AT"){
        check = 0;
        return;
    }
    cnt++;
}

void COLON(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "COLON"){
        check = 0;
        return;
    }
    cnt++;
}

void SCHEME(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "SCHEME"){
        check = 0;
        return;
    }
    cnt++;
}

void DOMAIN(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "DOMAIN"){
        check = 0;
        return;
    }
    cnt++;
}

void MAILDOMAIN(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "MAILDOMAIN"){
        check = 0;
        return;
    }
    cnt++;
}

void PATH(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "PATH"){
        check = 0;
        return;
    }
    cnt++;
}

void PHONENUM(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "PHONENUM"){
        check = 0;
        return;
    }
    cnt++;
}

void mail();

void uri(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    SCHEME();
    COLON();
    if(tks[cnt].first == "PATH"){
        mail();
    }
    else if(tks[cnt].first == "SLASH"){
        SLASH();
        SLASH();
        PATH();
        DOT();
        DOMAIN();
    }
    else if(tks[cnt].first == "PHONENUM"){
        PHONENUM();
    }
    else{
        check = 0;
    }
     
}

void mail(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    PATH();
    AT();
    MAILDOMAIN();
    DOT();
    DOMAIN();
}

void stmt(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first == "PATH"){
        mail();
    }
    else if(tks[cnt].first == "SCHEME"){
        uri();
    }
}

void program(){
    stmt();
}

signed main(){
    string s="";

    if(!scn()){
        cout << "Invalid input" << endl;
        return 0;
    }
    // for(int i=0;i<tks.size();i++){
    //     cout << tks[i].second<< ' ' << tks[i].first << endl;
    // }
    program();
    if(check){
        for(int i = 0;i < tks.size();i++){
            cout << tks[i].second << " " << tks[i].first << '\n';
        }
    }
    else cout << "Invalid input" << endl;

    return 0;
}