#include<iostream>
#include<vector>
#include<utility>
#include<regex>
using namespace std;

vector<pair<string, string> > tokens;
vector<string> results;
int now = 0;

bool stmts();
bool stmt();
bool primary();
bool primary_tail();

bool scanner(){
	string s;
	string p1 = "[A-Za-z_][A-Za-z0-9_]*", p2 = "\"[^\"]*\"";
	regex r1(p1);
	regex r2(p2);
	while(cin >> s){
		string tmp = "";
		for(char i:s){
			if(i == '('){
				if(tmp != ""){
					if(regex_match(tmp, r1)) tokens.emplace_back("ID", tmp);
					else if(regex_match(tmp, r2)) tokens.emplace_back("STRLIT", tmp);
					else return false;
					tmp = "";
				}
				tokens.emplace_back("LBR", "(");
			}
			else if(i == ')'){
				if(tmp != ""){
					if(regex_match(tmp, r1)) tokens.emplace_back("ID", tmp);
					else if(regex_match(tmp, r2)) tokens.emplace_back("STRLIT", tmp);
					else return false;
					tmp = "";
				}
				tokens.emplace_back("RBR", ")");
			}
			else if(i == '.'){
				if(tmp != ""){
					if(regex_match(tmp, r1)) tokens.emplace_back("ID", tmp);
					else if(regex_match(tmp, r2)) tokens.emplace_back("STRLIT", tmp);
					else return false;
					tmp = "";
				}
				tokens.emplace_back("DOT", ".");
			}
			else{
				tmp += i;
			}
		}
		if(tmp != ""){
			if(regex_match(tmp, r1)) tokens.emplace_back("ID", tmp);
			else if(regex_match(tmp, r2)) tokens.emplace_back("STRLIT", tmp);
			else return false;
			tmp = "";
		}
	}
	tokens.emplace_back("EOF", "$");
	return true;
}

bool ID(){
	if(tokens[now].first == "ID"){
		results.push_back("ID " + tokens[now].second + "\n");
		now++;
		return true;
	}
	return false;
}

bool STRLIT(){
	if(tokens[now].first == "STRLIT"){
		results.push_back("STRLIT " + tokens[now].second + "\n");
		now++;
		return true;
	}
	return false;
}

bool DOT(){
	if(tokens[now].first == "DOT"){
		results.push_back("DOT .\n");
		now++;
		return true;
	}
	return false;
}

bool LBR(){
	if(tokens[now].first == "LBR"){
		results.push_back("LBR (\n");
		now++;
		return true;
	}
	return false;
}

bool RBR(){
	if(tokens[now].first == "RBR"){
		results.push_back("RBR )\n");
		now++;
		return true;
	}
	return false;
}

bool stmts(){
	bool ret = true;
	if(tokens[now].first == "ID"){
		ret &= stmt();
		ret &= stmts();
	}
	else if(tokens[now].first == "STRLIT"){
		ret &= stmt();
		ret &= stmts();
	}
	else if(tokens[now].first == "EOF"){
		return true;
	}
	else return false;
	return ret;
}

bool stmt(){
	bool ret = true;
	if(tokens[now].first == "ID"){
		ret &= primary();
	}
	else if(tokens[now].first == "STRLIT"){
		ret &= STRLIT();
	}
	else if(stmts()) return true;
	else if(tokens[now].first == "RBR") return true;
	else return false;
	return ret;
}



bool primary(){
	bool ret = true;
	if(tokens[now].first == "ID"){
		ret &= ID();
		ret &= primary_tail();
	}
	else return false;
	return ret;
}

bool primary_tail(){
	bool ret = true;
	if(tokens[now].first == "DOT"){
		ret &= DOT();
		ret &= ID();
		ret &= primary_tail();
	}
	else if(tokens[now].first == "LBR"){
		ret &= LBR();
		ret &= stmt();
		ret &= RBR();
		ret &= primary_tail();
	}
	else if(tokens[now].first == "RBR") return true;
	else if(tokens[now].first == "EOF"){
		return true;
	}
	else if(stmts()) return true;
	else return false;
	return ret;
}

bool program(){
	return stmts();
}

int main(){
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	if(!scanner()){
		cout << "invalid input";
		return 0;
	}
	//for(auto i:tokens) cout << i.first << " " << i.second << "\n";
	if(!program()){
		cout << "invalid input";
	}
	else{
		for(string i:results) cout << i;
	}
}
