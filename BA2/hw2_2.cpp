# include <iostream>
# include <map>
# include <vector>
# include <set>
using namespace std;

map<char, bool> vis;
map<char, vector<string>> path;
map<char, bool> lambda;
map<char, set<char>> firstset;

set<char> checkFirstSet(char current){
    if(vis[current] == 1) return firstset[current];
    vis[current] = 1;
    set<char> thisset;
    for(int i=0;i<path[current].size();i++){
        bool canEmpty = 1;
        for(char j:path[current][i]){
            if(islower(j) || j == '$'){
                thisset.insert(j);
                canEmpty = 0;
                break;
            }
            else if(isupper(j)){
                set<char> tmp = checkFirstSet(j);
                for(char i:tmp){
                    if(i != ';') thisset.insert(i);
                }
                if(tmp.find(';') == tmp.end()){
                    canEmpty = 0;
                    break;
                }
            }
        }
        if(canEmpty) thisset.insert(';');
    }
    firstset[current] = thisset;
    return thisset;
}

void parse(){
    string s1, s2;

    while(1){
        cin >> s1;
        if(s1 == "END_OF_GRAMMAR") break;
        cin >> s2;
        vis[s1[0]] = 0; // vis
        string tmppath;
        vector<string> longpath;
        bool checklbda = 0;
        for(int i=0;i<s2.length();i++){
            if(s2[i] == ';') {
                lambda[s1[0]] = 1; // lambda
                checklbda = 1;
            }
            if(s2[i] == '|'){
                if(tmppath != ""){
                    longpath.push_back(tmppath);
                    tmppath = "";
                }
            }
            else tmppath += s2[i];
        }
        if(tmppath != "") longpath.push_back(tmppath);
        path[s1[0]] = longpath;
        if(!checklbda) lambda[s1[0]] = 0; // lambda
        // if(lambda[s1[0]] != 1) lambda[s1[1]] = 0; // lambda
        set<char> tmp;
        firstset[s1[0]] = tmp; // firstset
    }
    // for(auto i:path){
    //     cout << i.first << ' ';
    //     // cout << i.second;
    //     for(auto j:i.second){
    //         cout << j << ' ';
    //     }
    //     cout << '\n';
    // }
}


signed main(){
    parse();

    
    for(auto i:path){
        checkFirstSet(i.first);
    }
    for(auto i:firstset){
        cout << i.first << ' ';
        // set<char> tmp = checkFirstSet(i.first);
        for(char j:i.second){
            cout << j;
        }
        cout << '\n';
    }
    cout << "END_OF_FIRST" << '\n';
    return 0;
}