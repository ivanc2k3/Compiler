#include<bits/stdc++.h>
using namespace std;

#define ll long long
vector<pair<string, string>> input_tokens;
int position = 0;

bool stmt();
bool stmts();
bool primary();
bool primary_tail();
bool program();
bool check_end(int num);

string get_inputs(){
    string input_stream = "";
    string input;
    while(cin>>input){
        if(input == "__EOF__") break;
        input_stream += input;
    }
    return input_stream;
}

bool scanner(string input){
    regex id_regex("[A-Za-z_][A-Za-z0-9_]*");
    regex strlit_regex("\"[^\"]*\"");
    pair<string, string> tmp = {"", ""};
    for(char& c: input){
        // cout<<c<<endl;
        if(c == '(' || c == ')' || c == '.'){
            if(tmp.first != ""){
                input_tokens.push_back({tmp.first, tmp.second});
                tmp = {"", ""};
            }
            else{
                if(tmp.second != "") return false;
            }
            if(c == '('){
                input_tokens.push_back({"LBR", "("});
            }
            else if(c == ')'){
                input_tokens.push_back({"RBR", ")"});
            }
            else if(c == '.'){
                input_tokens.push_back({"DOT", "."});
            }
        }
        else{
            tmp.second += c;
            string tmp2 = "";
            tmp2 += c;
            if(regex_match(tmp.second, id_regex)){
                tmp.first = "ID";
            }
            else if(regex_match(tmp.second, strlit_regex)){
                tmp.first = "STRLIT";
            }
            else if(tmp.first != ""){
                input_tokens.push_back({tmp.first, tmp.second.substr(0, tmp.second.size() - 1)});
                if(regex_match(tmp2, id_regex)){
                    tmp = {"ID", tmp2};
                }
                else{
                    tmp = {"", tmp2};
                }
            }
        }
    }
    if(tmp.first != ""){
        input_tokens.push_back({tmp.first, tmp.second});
    }
    else{
        if(tmp.second != "") return false;
    }
    return true;
}

bool check_end(int num){
    if(position + num >= input_tokens.size()){
        return true;
    }
    else{
        return false;
    }
}

bool stmts(){
    if(check_end(0)) return true;
    bool ret = stmt();
    if(ret){
        stmts();
    }
    return ret;
}

bool stmt(){
    if(check_end(0)) return true;
    if(input_tokens[position].first == "ID"){
        return primary();
    }
    else if(input_tokens[position].first == "STRLIT"){
        position++;
        return true;
    }
    else return false;
}

bool primary(){
    position++;
    return primary_tail();
}

bool primary_tail(){
    if(check_end(0)) return true;
    if(input_tokens[position].first == "DOT"){
        if(!check_end(1)){
            if(input_tokens[position + 1].first == "ID"){
                position += 2;
                return primary_tail();
            }
            else return false;
            
        }
        else return false;
        
    }
    else if(input_tokens[position].first == "LBR"){
        position += 1;
        bool ret = stmt();
        if(check_end(0)) return false;
        if(ret && input_tokens[position].first == "RBR"){
            position += 1;
            return primary_tail();
        }
        else return false;
        
    }
    return true;
}

bool program(){
    return stmts();
}

int main(){
    string input_stream = get_inputs();
    if(!scanner(input_stream)){
        cout<<"invalid input"<<endl;
        return 0;
    }
    if(program()){
        for(pair<string, string> p: input_tokens){
            cout<<p.first<<" "<<p.second<<endl;
        }
        return 0;
    }
    else{
        cout<<"invalid input"<<endl;
        return 0;
    }
}