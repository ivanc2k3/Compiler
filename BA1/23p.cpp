# include <iostream>
# include <vector>
# include <set>
using namespace std;

vector<pair<string, string>> tks;

bool isid(string s){
    if(!(s[0] >= 'A' and s[0] <= 'Z')) return 0;
    if(s.length() != 10) return 0;
    for(int i = 1;i < s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}

bool isnationnum(string s){
    if(s.length() != 3) return 0;
    for(int i=0;i<s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}

bool isphonenum(string s){
    if(s.length() != 9) return 0;
    if(s[0] != '9') return 0;
    for(int i=1;i<s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}

bool isyear(string s){
    if(s.length() != 4) return 0;
    if(!(s[0] == '1' || s[0] == '2')) return 0;
    for(int i=1;i<s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}

bool ismonth(string s){
    set<string> st = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    if(st.count(s)) return 1;
    return 0;
}

bool isday(string s){
    set<string> st;
    for(int i=1;i<=31;i++){
        st.insert(to_string(i));
    }
    if(st.count(s)) return 1;
    else return 0;
}

bool isdigit(char c){
    if((c >= '0' and c <= '9')) return 1;
    return 0;
}

bool isupper(char c){
    if(c >= 'A' and c <= 'Z')
        return 1;
    return 0;
}

bool scn(){
    string s;

    cin >> s;
    pair<string, string> tp; // terminal, string
    string tmps = "";string tmpd = "";
    bool flag = 0;
    if(isupper(s[0])) flag = 0;
    else if(isdigit(s[0])) flag = 1;
    for(int i=0;i<s.length();i++){
        if(!(isdigit(s[i]) || isupper(s[i]) || s[i] == '+' || s[i] == '.' || s[i] == '(' || s[i] == ')' || s[i] == '/' )) return 0;
        if(isupper(s[i])){
            if(flag == 1) return 0;
            tmps+=s[i];
            flag = 0;
        } 
        else if(isdigit(s[i])){
            if(flag == 0 && tmps.length() != 1 && tmps.length() != 0) return 0;
            tmpd+=s[i];
            flag = 1;
        } 
        if(s[i] == '+' || s[i] == '.' || s[i] == '(' || s[i] == ')' || s[i] == '/' || i == s.length() - 1){
            if(tmps.length() == 1 && tmpd.length() != 0){
                tmps += tmpd;
                if(isid(tmps)){
                    tks.push_back({"ID", tmps});
                    tmps = "";tmpd = "";
                }
                else return 0;
            }
            else if(tmps.length() == 3){
                if(ismonth(tmps)){
                    tks.push_back({"MONTH", tmps});
                    tmps = "";tmpd = "";
                }
                else return 0;
            }
            else if(tmps.length() != 0) return 0;
            else if(isnationnum(tmpd)){
                tks.push_back({"NATIONNUM", tmpd});
                tmps = "";tmpd = "";
            }
            else if(isphonenum(tmpd)){
                tks.push_back({"PHONENUM", tmpd});
                tmps = "";tmpd = "";
            }
            else if(isyear(tmpd)){
                tks.push_back({"YEAR", tmpd});
                tmps = "";tmpd = "";
            }
            else if(isday(tmpd)){
                tks.push_back({"DAY", tmpd});
                tmps = "";tmpd = "";
            }
            if(s[i] == '+') tks.push_back({"PLUS", "+"});
            else if(s[i] == '.') tks.push_back({"DOT", "."});
            else if(s[i] == '(') tks.push_back({"LBR", "("});
            else if(s[i] == ')') tks.push_back({"RBR", ")"});
            else if(s[i] == '/') tks.push_back({"SLASH", "/"});
        }
    }
    return 1;
}

bool check = 1;
int cnt = 0;

void RBR(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "RBR"){
        check = 0;
        return;
    }
    cnt++;
}

void LBR(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "LBR"){
        check = 0;
        return;
    }
    cnt++;
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

void PLUS(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "PLUS"){
        check = 0;
        return;
    }
    cnt++;
}

void MONTH(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "MONTH"){
        check = 0;
        return;
    }
    cnt++;
}

void YEAR(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "YEAR"){
        check = 0;
        return;
    }
    cnt++;
}

void DAY(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "DAY"){
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

void NATIONNUM(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "NATIONNUM"){
        check = 0;
        return;
    }
    cnt++;
}

void ID(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "ID"){
        check = 0;
        return;
    }
    cnt++;
}

void phone(){
    PLUS();
    LBR();
    NATIONNUM();
    RBR();
    PHONENUM();
}

void date(){
    if(tks[cnt].first == "MONTH"){
        MONTH();
        DOT();
        DAY();
        DOT();
        YEAR();
    }
    else if(tks[cnt].first == "YEAR"){
        YEAR();
        SLASH();
        MONTH();
        SLASH();
        DAY();
    }
}

void stmt(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    else if(tks[cnt].first == "ID"){
        ID();
    }
    else if(tks[cnt].first == "PLUS"){
        phone();
    }
    else if(tks[cnt].first == "MONTH" || tks[cnt].first == "YEAR"){
        date();
    }
}

void program(){
    stmt();
}
signed main(){

    if(!scn()){
        cout << "invalid input" << endl;
        return 0;
    }
    // for(int i=0;i<tks.size();i++){
    //     cout << tks[i].second << ' ' << tks[i].first << endl;
    // }
    program();
    if(check){
        for(int i = 0;i < tks.size();i++){
            cout << tks[i].first << " " << tks[i].second << '\n';
        }
    }
    else cout << "invalid input" << endl;

    

    return 0;
}