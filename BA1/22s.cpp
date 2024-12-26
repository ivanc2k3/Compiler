# include <iostream>
# include <vector>
# include <set>
using namespace std;

bool isNum(string s) {
    if(s.length()<1) return 0;
    if(!(s[0] >= '1' and s[0] <= '9')) return 0;
    if(s=="0") return 1;
    for(int i=1;i<s.length();i++){
        if(!(s[i] >= '0' and s[i] <= '9')) return 0;
    }
    return 1;
}

bool isid(string s){
    if(s.length()<1) return 0;
    for(int i=0;i<s.length();i++){
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))) return 0;
    }
    return 1;
}

bool isdigit(char c){
    if((c >= '0' and c <= '9')) return 1;
    return 0;
}

bool ischar(char c){
    if((c >= 'A' and c <= 'Z') || (c >= 'a' and c <= 'z'))
        return 1;
    return 0;
}

signed main(){
    string s;

    while(cin>>s){
        string tps = ""; string tpd = "";
        
    }


    return 0;
}