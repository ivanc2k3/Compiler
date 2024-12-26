#include<iostream>
#include<vector>
#include<map>
using namespace std;

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

bool scn(){
    string s;

    while(cin >> s){
        int len = s.length();

        for(int i = 0;i < len;i++){
            if(isIDchar(s[i])){
                string tmp = "";
                int j;

                for(j = i;j < len;j++){
                    if(isIDchar(s[j])){
                        tmp += s[j];
                    }
                    else if(!isIDchar(s[j]) && tmp != ""){
                        tks.push_back({"ID", tmp});
                        tmp.clear();
                        break;
                    }

                }
            }
        }

    }
}

signed main(){


    return 0;
}