# include <iostream>
# include <vector>
# include <regex>
using namespace std;

vector<pair<string, string>> tks; // terminal, s

bool scn(){
    string s;
    regex pattern1("[A-Za-z_][A-Za-z0-9_]*");
    regex pattern2("\"[^\"]*\"");

    while(cin >> s){
        //string tmps;
        pair<string, string> tp; // s, terminal
        for(int i = 0;i < s.length();i++){
            if(s[i] == '('){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.second, tp.first});
                    tp.first = ""; tp.second = "";
                }
                tks.push_back({"LBR", "("});
            }
            else if(s[i] == ')'){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.second, tp.first});
                    tp.first = ""; tp.second = "";
                } 
                tks.push_back({"RBR", ")"});
            }
            else if(s[i] == '.'){
                if(tp.first != "" && tp.second != ""){
                    tks.push_back({tp.second, tp.first});
                    tp.first = ""; tp.second = "";
                }
                tks.push_back({"DOT", "."});
            }
            else{
                if(tp.first != ""){
                    if(tp.second == "STRLIT"){
                        tks.push_back({tp.second, tp.first});
                        tp.first = ""; tp.second = "";
                    }
                    else if(s[i] == '\"'){
                        if(tp.second == "ID"){
                            tks.push_back({tp.second, tp.first});
                            tp.first = ""; tp.second = "";
                        }
                    }
                }
                tp.first += s[i];
                if(regex_match(tp.first, pattern1)) tp.second = "ID";
                else if (regex_match(tp.first, pattern2)) tp.second = "STRLIT";
                else tp.second = "";
            }
        }    
        if(tp.first != ""){
            if(tp.second != ""){
                tks.push_back({tp.second, tp.first});
            }
            else{
                return 0;
            }
        }
    }
    tks.push_back({"EOF", "EOF"});
    return 1;
}

int cnt = 0;
string ans = "";
bool stmt();
bool stmts();

bool ID(){
    if(tks[cnt].first == "ID"){
        ans += "ID " + tks[cnt].second + '\n';
        cnt++;
        return 1;
    }
    else return 0;
}

bool DOT(){
    if(tks[cnt].first == "DOT"){
        ans += "DOT " + tks[cnt].second + '\n';
        cnt++;
        return 1;
    }
    else return 0;
}

bool LBR(){
    if(tks[cnt].first == "LBR"){
        ans += "LBR " + tks[cnt].second + '\n';
        cnt++;
        return 1;
    }
    else return 0;
}

bool RBR(){
    if(tks[cnt].first == "RBR"){
        ans += "RBR " + tks[cnt].second + '\n';
        cnt++;
        return 1;
    }
    else return 0;
}

bool STRLIT(){
    if(tks[cnt].first == "STRLIT"){
        ans += "STRLIT " + tks[cnt].second + '\n';
        cnt++;
        return 1;
    }
    else return 0;
}

bool primary_tail(){
    if(tks[cnt].first == "DOT"){
        if(DOT() && ID() && primary_tail()) return 1;
    }
    else if(tks[cnt].first == "LBR"){
        if(LBR() && stmt() && RBR() && primary_tail()) return 1;
    }
    else if(tks[cnt].first == "EOF") return 1;
    else if(tks[cnt].first == "RBR") return 1; // situation: (haha)
    else if(stmts()) return 1; // when primary_tail is empty, it will check stmts(line 2)
    return 0;
}

bool primary(){
    if(tks[cnt].first == "ID"){
        if(ID() && primary_tail()) return 1;
    }
    return 0;
}

bool stmt(){
    if(tks[cnt].first == "ID"){
        if(primary()) return 1;
    }
    else if(tks[cnt].first == "STRLIT"){
        if(STRLIT()) return 1;
    }
    else if(tks[cnt].first == "RBR") return 1; // situation:()
    else if(stmts()) return 1; // line 2, when stmt() is empty
    return 0;
}

bool stmts(){
    if(tks[cnt].first == "ID"){
        if(stmt() && stmts()) return 1;
    }
    else if(tks[cnt].first == "STRLIT"){
        if(STRLIT() && stmts()) return 1; // check stmts()
    }
    else if(tks[cnt].first == "EOF") return 1;
    return 0;
}

bool program(){
    return stmts();
}

signed main(){

    if(!scn()){
        cout << "invalid input" << '\n';
        return 0;
    } 
    // for(auto i: tks){
    //     cout << i.first << " " << i.second << endl;
    // }
    if(program()) cout << ans;
    else cout << "invalid input" << '\n';

    return 0;
}