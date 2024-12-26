# include <iostream>
# include <vector>
using namespace std;
// ssh dd@2356336901 -p 59698
// scp -r -P 59698 dd@2356336901:~/pull/ ./pull/
// scp -r -P 59698 ./pull/ dd@2356336901:~/

vector<pair<string, string>> tks; // terminal, string
bool check = 1;

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

bool checkpattern1(string s){
    for(int i = 0;i < s.length();i++){
        if(!isIDchar(s[i])) return 0;
    }
    return 1;
}

bool checkpattern2(string s){
    if(s.length()<2) return 0;
    if(s[0] != '\"') return 0;
    if(s[s.length() - 1] != '\"') return 0;
    for(int i=1;i < s.length() - 1;i++){
        if(s[i] == '\"') return 0;
    }

    return 1;
}

bool scn(){
    string s;

    while(getline(cin, s)){
        pair<string, string> tp; // terminal, string
        bool checkear = 0;

        for(int i = 0;i < s.length(); i++){
            if(!checkear && s[i] == ' ') continue;
            if(s[i] == '(' && !checkear){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.first, tp.second});
                    tp.first = ""; tp.second = "";
                }
                tks.push_back({"LBR", "("});
            }
            else if(s[i] == ')' && !checkear){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.first, tp.second});
                    tp.first = ""; tp.second = "";
                }
                tks.push_back({"RBR", ")"});
            }
            else if(s[i] == '.' && !checkear){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.first, tp.second});
                    tp.first = ""; tp.second = "";
                }
                tks.push_back({"DOT", "."});
            }
            else{
                if(tp.second != ""){
                    if(tp.first == "STRLIT"){
                        tks.push_back({tp.first, tp.second});
                        tp.first = ""; tp.second = "";
                    }
                    else if(s[i] == '\"' && tp.first == "ID"){
                        tks.push_back({tp.first, tp.second});
                        tp.first = ""; tp.second = "";
                    }
                }
                if(s[i] == '\"') checkear = not checkear;
                tp.second += s[i];
                if(checkpattern1(tp.second)) tp.first = "ID";
                else if(checkpattern2(tp.second)) tp.first = "STRLIT";
                else tp.first = "";        
            }
        }
        if(tp.second != ""){
            if(tp.first != ""){
                tks.push_back({tp.first, tp.second});
            }
            else return 0;
        }
    }
    return 1;
}
int cnt = 0;

void stmt();
void stmts();

void STRLIT(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first != "STRLIT"){
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

void primary_tail(){
    if(check == 0) return;
    if(cnt >= tks.size()) return;
    else if(tks[cnt].first == "DOT"){
        DOT();
        ID();
        primary_tail();
    }
    else if(tks[cnt].first == "LBR"){
        LBR();
        stmt();
        RBR();
        primary_tail();
    }
    else if(tks[cnt].first == "RBR") return;
    
}

void primary(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    ID();
    primary_tail();
}

void stmt(){
    if(check == 0) return;
    if(cnt >= tks.size()){
        return;
    }
    if(tks[cnt].first == "RBR") return;
    else if(tks[cnt].first == "ID"){
        primary();
    }
    else if(tks[cnt].first == "STRLIT"){
        STRLIT();
    }
}

void stmts(){
    if(check == 0) return;
    if(cnt >= tks.size()) return;
    stmt();
    stmts();
}

void program(){
    stmts();
}

signed main(){


    try{
        if(!scn()){
            cout << "invalid input" << endl;
            return 0;
        }
        // for(int i=0;i<tks.size();i++){
        //     cout << tks[i].first << tks[i].second << endl;
        // }
        program();
        if(check){
            for(int i = 0;i < tks.size();i++){
                cout << tks[i].first << " " << tks[i].second << '\n';
            }
        }
        else cout << "invalid input" << endl;

    }
    catch(...){
        cout << "invalid input" << endl;
    }

    return 0;
}