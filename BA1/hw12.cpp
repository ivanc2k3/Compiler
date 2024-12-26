# include <iostream>
# include <map>
using namespace std;
map<char,string> mp = {{'+', "PLUS"}, {'-', "MINUS"}, {'*', "MUL"}, {'/', "DIV"}, {'(', "LPR"}, {')', "RPR"}};

bool isnum(char c){
    bool re = 0;
    if(int(c) >= 48 && int(c) <= 57) re = 1;
    return re;
}

signed main(){
    string s,ret;
    ios::sync_with_stdio(0);cin.tie(0);

    while(cin >> s){
        string tmp;
        for(int i = 0;i < s.size();i++){
            if(tmp != "" && !isnum(s[i])){
                cout << "NUM" << " " << tmp << '\n';
                tmp = "";
            }
            else if(isnum(s[i])) tmp += s[i];
            if(!isnum(s[i])){
                cout << mp[s[i]] << '\n';
            }
        }
        if(tmp != "") cout << "NUM"<< " " << tmp << '\n';
    }



    return 0;
}