# include <iostream>
# include <regex>
using namespace std;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string s = "";
    regex pattern2("\"[^\"]*\"");

    cout<<(regex_match("\"[]\"", pattern2));
    return 0;
}