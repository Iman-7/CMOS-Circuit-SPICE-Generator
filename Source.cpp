#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> SPICE(0);
vector<string> expressions(0);
int wires = 1;
int gates_out = 0;
string out;
string start = "Z";

string NOT(char in) {

	int idx = SPICE.size();
	SPICE.resize(SPICE.size() + 2);
	for (int i = idx; i < SPICE.size(); i++)
		SPICE[i].resize(6);
	string s = " ";
	if (!isupper(in))
		s[0] = toupper(in);
	else
		s[0] = tolower(in);
	SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = s[0]; SPICE[idx][2] = in; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
	idx++;
	SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = s[0]; SPICE[idx][2] = in; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
	gates_out++;
	return s;

}

void update_operation(vector <bool>& operation, string bool_exp) {
	operation.resize(bool_exp.length());
	for (int i = 0; i < bool_exp.length(); i++) {

		if (bool_exp[i] == '&' || bool_exp[i] == '|' || bool_exp[i] == '\'' || bool_exp[i] == '=' || bool_exp[i] == '(' || bool_exp[i] == ')')
			operation[i] = true;
		else
			operation[i] = false;
	}
}

string converting(string exp) {
	int idx = exp.find('=');
	vector <bool> operation(exp.size(), false);

	string no = "'";
	string andd = "&";
	string orr = "|";
	for (int i = idx + 1; i < exp.length(); i++)
	{
		update_operation(operation, exp);
		if (!operation[i])
		{
			if (i < exp.length() - 1) {
				if (exp[i + 1] == '\'')
					exp.erase(i + 1, 1);
				else
					exp.insert(i + 1, no);
			}
			else
				exp.append(no);
		}

		else
		{
			if (exp[i] == '&')
				exp.replace(i, 1, orr);
			else if (exp[i] == '|')
				exp.replace(i, 1, andd);
		}
	}
	return exp;
}

string AND_PMOS(char a, char b) {

	int idx;
	if (int(a) >= 65 && int(a) <= 122 && int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 2);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
		idx++;
		wires++;
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = to_string(wires-1); SPICE[idx][4] = to_string(wires - 1); SPICE[idx][5] = "PMOS";
		wires++;
		//gates_out++;
	}

	else if (int(a) >= 65 && int(a) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = b; SPICE[idx][4] = b; SPICE[idx][5] = "PMOS";
		wires++;
		//gates_out++;
	}
	else if (int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = a; SPICE[idx][4] = a; SPICE[idx][5] = "PMOS";
		wires++;
		//gates_out++;
	}
	if (wires - 1 > 9) return "Error AND";
	return to_string(wires - 1);
}

string OR_PMOS(char a, char b) {

	int idx;
	if (int(a) >= 65 && int(a) <= 122 && int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 2);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
		idx++;
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
		wires++;
		//gates_out++;
	}

	else if (int(a) >= 65 && int(a) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = b; SPICE[idx][2] = a; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
		//gates_out++;
	}
	else if (int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = a; SPICE[idx][2] = b; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
		//gates_out++;
	}
	else
	{
		int min;
		int max;
		if (int(a) < int(b))
		{
			min = a;
			max = b;
		}
		else
		{
			min = b;
			max = a;
		}

		for (int i = 0; i < SPICE.size(); i++)
		{
			if (SPICE[i][1] == to_string(max))
				SPICE[i][1] = to_string(min);
		}
	}

	if (wires - 1 > 9) return "Error OR";
	else
	return to_string(wires - 1);
}

string AND_NMOS(char a, char b) {

	int idx;
	if (int(a) >= 65 && int(a) <= 122 && int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 2);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
		idx++;
		wires++;
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = to_string(wires - 1); SPICE[idx][4] = to_string(wires - 1); SPICE[idx][5] = "NMOS";
		wires++;
		//gates_out++;
	}

	else if (int(a) >= 65 && int(a) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = b; SPICE[idx][4] = b; SPICE[idx][5] = "NMOS";
		wires++;
		//gates_out++;
	}
	else if (int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = a; SPICE[idx][4] = a; SPICE[idx][5] = "NMOS";
		wires++;
		//gates_out++;
	}
	if (wires - 1 > 9) return "Error AND";
	return to_string(wires - 1);
}

string OR_NMOS(char a, char b) {

	int idx;
	if (int(a) >= 65 && int(a) <= 122 && int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 2);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = a; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
		idx++;
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = to_string(wires); SPICE[idx][2] = b; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
		wires++;
		//gates_out++;
	}

	else if (int(a) >= 65 && int(a) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = b; SPICE[idx][2] = a; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
		//gates_out++;
	}
	else if (int(b) >= 65 && int(b) <= 122)
	{
		idx = SPICE.size();
		SPICE.resize(SPICE.size() + 1);
		for (int i = idx; i < SPICE.size(); i++)
			SPICE[i].resize(6);
		SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = a; SPICE[idx][2] = b; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
		//gates_out++;
	}
	else
	{
		int min;
		int max;
		if (int(a) < int(b))
		{
			min = a;
			max = b;
		}
		else
		{
			min = b;
			max = a;
		}

		for (int i = 0; i < SPICE.size(); i++)
		{
			if (SPICE[i][1] == to_string(max))
				SPICE[i][1] = to_string(min);
		}
	}

	if (wires - 1 > 9) return "Error OR";
	else
		return to_string(wires - 1);
}

void connect_out(int ooo, string maybe) {
	for (int i = ooo; i < SPICE.size(); i++)
		if (SPICE[i][1] == to_string(wires - 1) || SPICE[i][1] == "1" + to_string(wires - 1) || SPICE[i][1] == maybe) 
			SPICE[i][1] = out;
		
}

void PUN(string exp) {
	int ooo = SPICE.size();
	int x = exp.find('=');
	out.assign(exp, 0, x);
	exp.erase(0, x + 1);
	bool detector = false;
	vector <bool> operation(exp.size(), false);
	for (int i = 1; i < exp.length(); i++)
	{
		detector = false;
		update_operation(operation, exp);
		if (operation[i - 1] == false && exp[i] != '\'')
		{
			string inverted;
			inverted = NOT(exp[i - 1]);
			exp.replace(i - 1, 1, inverted);
		}

		else if (exp[i] == '\'') {
			detector = true;
			exp.erase(i, 1);
		}
		
	}

	update_operation(operation, exp);
	if (operation[exp.length()-1] == false && !detector)
	{
		string inverted;
		inverted = NOT(exp[exp.length() - 1]);
		exp.replace(exp.length() - 1, 1, inverted);
	}

	int idx;
	int first; 
	int second;
	char a;
	char b;

	while (exp.find('&') <= exp.length())
	{
		update_operation(operation, exp);
		idx = exp.find('&');
		first = idx - 1;
		second = idx + 1;
		string result;
		a = exp[first];
		b = exp[second];
		result = AND_PMOS(a, b);
		exp.erase(idx - 1, 3);
		exp.insert(idx - 1, result);
	}

	while (exp.find('|') <= exp.length())
	{
		update_operation(operation, exp);
		idx = exp.find('|');
		first = idx - 1;
		second = idx + 1;
		string result;
		a = exp[first];
		b = exp[second];
		result = OR_PMOS(a, b);
		exp.erase(idx - 1, 3);
		exp.insert(idx - 1, result);
	}

	connect_out(ooo, "lol");
}

void PDN(string exp) {
	int ooo = SPICE.size();
	string out;
	int x = exp.find('=');
	out.assign(exp, 0, x);
	exp.erase(0, x + 1);

	vector <bool> operation(exp.size(), false);
	for (int i = 0; i < exp.length() - 1; i++)
	{
		update_operation(operation, exp);
		if (operation[i] == false && exp[i+1] == '\'')
		{
			if (!isupper(exp[i]))
				exp[i] = toupper(exp[i]);
			else
				exp[i] = tolower(exp[i]);
			exp.erase(i + 1, 1);
		}
	}

	int idx;
	int first;
	int second;
	char a;
	char b;


	while (exp.find('|') <= exp.length())
	{
		update_operation(operation, exp);
		idx = exp.find('|');
		first = idx - 1;
		second = idx + 1;
		string result;
		a = exp[first];
		b = exp[second];
		result = OR_NMOS(a, b);
		exp.erase(idx - 1, 3);
		exp.insert(idx - 1, result);
	}

	while (exp.find('&') <= exp.length())
	{
		update_operation(operation, exp);
		idx = exp.find('&');
		first = idx - 1;
		second = idx + 1;
		string result;
		a = exp[first];
		b = exp[second];
		result = AND_NMOS(a, b);
		exp.erase(idx - 1, 3);
		exp.insert(idx - 1, result);
	}
	connect_out(ooo, "lol");
}

void print() {
	for (int i = 0; i < SPICE.size(); i++)
	{
		if (SPICE[i][0] != "deleted")
		{
			for (int j = 0; j < 6; j++)
				cout << SPICE[i][j] << " ";
			cout << endl;
		}
	}
}

void semi(string exp) {
	int idx;
	string e;
	while (exp.find(';') <= exp.length()) {
		idx = exp.find(';');
		e.assign(exp, 0, idx);
		exp.erase(0, idx + 1);
		expressions.push_back(e);
	}
	if (!exp.empty())
		expressions.push_back(exp);
}

bool validity(string exp) {
	int idx = exp.find('=');
	out.assign(exp, 0, idx);

	if (idx > exp.length())
	{
		cout << endl;
		cout << "Invalid Expression." << endl;
		cout << "Error: The output and input cannot be determined." << endl;
		return true;
	}

	if (exp.length() <= 3)
	{
		cout << endl;
		cout << "Invalid Expression." << endl;
		cout << "Error: There is no operations in your expression." << endl;
		return true;
	}

	vector <bool> operation(exp.size(), false);
	update_operation(operation, exp);

	int right = 0;
	int left = 0;
	for (int i = 0; i < operation.size()-1; i++) {
		if (exp[i] == '(')
			right++;
		if (exp[i] == ')')
			left++;

		if (exp[i+1] == ' ')
		{
			cout << endl;
			cout << "Invalid Expression." << endl;
			cout << "Error: Spaces are not allowed in the input expressions." << endl;
			return true;
		}

		if(!operation[i] && !operation[i+1])
		{
			cout << endl;
			cout << "Invalid Expression." << endl;
			cout << "Error: Each variable should consist of a single character." << endl;
			return true;
		}
	}

	if (exp[exp.size() - 1] == '(') right++; else if (exp[exp.size() - 1] == ')') left++;
	
	if (right != left)
	{
		cout << endl;
		cout << "Invalid Expression." << endl;
		cout << "Error: Parentheses are not equivalent in your expression" << endl;
		return true;
	}

	for (int i = idx; i < exp.size(); i++)
	{
		if (out[0] == exp[i])
		{
			cout << endl;
			cout << "Invalid Expression." << endl;
			cout << "Error: The output cannot be one of the statement's inputs." << endl;
			return true;
		}
	}
	return false;
}

void remove_duplicates() {
	bool detector = false;
	int inc = 0;
	string str;
	int strInt;
	for (int i = 0; i < SPICE.size() - 1; i++) {
		detector = false;
		inc = 0;
		for (int j = i + 1; j < SPICE.size(); j++)
		{ //y=a|b;x=y&a;z=x&a
			//cout << j << endl;
			if (SPICE[j][0] != "deleted")
			{
				if (detector)
				{
					str.assign(SPICE[j][0], 1, SPICE[j][0].length() - 1);
					strInt = stoi(str) - inc;
					SPICE[j][0].erase(1, SPICE[j][0].length() - 1);
					SPICE[j][0].append(to_string(strInt));
				}

				if (SPICE[i][1] == SPICE[j][1] && SPICE[i][2] == SPICE[j][2] && SPICE[i][3] == SPICE[j][3] && SPICE[i][4] == SPICE[j][4] && SPICE[i][5] == SPICE[j][5])
				{
					//cout << "deleted" << endl;
					inc++;
					detector = true;
					SPICE[j][0] = "deleted";
				}
			}
		}
	}
}

void only_not(string exp) {
	string first = exp.substr(0, 1);
	string second = exp.substr(2, 1);
	int idx = SPICE.size();
	SPICE.resize(SPICE.size() + 2);
	for (int i = idx; i < SPICE.size(); i++)
		SPICE[i].resize(6);
	SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = first; SPICE[idx][2] = second; SPICE[idx][3] = "VDD"; SPICE[idx][4] = "VDD"; SPICE[idx][5] = "PMOS";
	idx++;
	SPICE[idx][0] = "M" + to_string(idx); SPICE[idx][1] = first; SPICE[idx][2] = second; SPICE[idx][3] = "0"; SPICE[idx][4] = "0"; SPICE[idx][5] = "NMOS";
	gates_out++;
	return;
}

void proccessing(string exp)
{
	if (exp.length() == 4)
	{
		only_not(exp);
		return;
	}
	PUN(exp);
	exp = converting(exp);
	PDN(exp);
}

vector <vector <int>> bonus_helper(vector <int>& focus, string exp) {
	vector <bool> served(exp.size(), false);
	vector <vector <int>> index(exp.size());
	for (int i = 0; i < index.size(); i++)
		index[i].resize(2);

	int num = 0;
	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == '(')
		{
			do num++;
			while (served[num] == true);
			focus[i] = num;
			index[num][0] = i;
		}
		if (exp[i] == ')')
		{
			focus[i] = num;
			index[num][1] = i;
			served[num] = true;
			do num--;
			while (served[num] == true);
		}
	}
	return index;
}

void bonus(string exp)
{
	vector <int> focus(exp.size(), 0);
	vector <vector <int>> index(exp.size());
	for (int i = 0; i < index.size(); i++)
		index[i].resize(2);
	index = bonus_helper(focus, exp);

	int maxi =  focus[0];
	for (int i = 1; i < focus.size(); i++)
		if (maxi < focus[i])
			maxi = focus[i];
	maxi++;

	
	//y=((a|b)&(c|d)’)’
	//0012000203000301

	int idx1;
	int idx2;
	string str;
	string pre;
	string part;
	string sta;
	string equal = "=";
	if (maxi > 1)
	{
		cout << endl;
		cout << "The expression simplification: " << endl;
	}
	while (--maxi)
	{
		focus.resize(exp.length());
		for (int i = 0; i < focus.size(); i++)
			focus[i] = 0;
		index = bonus_helper(focus, exp);
		idx1 = index[maxi][0];  
		idx2 = index[maxi][1];  
		str = exp.substr(idx1 + 1, idx2 - idx1 - 1);
		pre = start + equal;
		part = pre + str;
		proccessing(part);
		exp.erase(idx1, idx2 - idx1 + 1);
		exp.insert(idx1, start);
		start[0]--;
		cout << exp << endl;
	}
	
	if (exp.find('&') <= exp.length() || exp.find('|') <= exp.length() || exp.find('\'') <= exp.length())
		proccessing(exp);
	else
	{
		string lol = exp.substr(2, 1);
		lol[0]++;
		out = exp.substr(0, 1);
		connect_out(0, lol);
	}
}



int main() {
	string exp;
	cout << "Enter your expression : (separate by ';' for multiple statements)" << endl;
	cout << "Note: In case of using Parentheses, don't use character (from U to Z) or (from u to z)" << endl;
	getline(cin, exp);
	
	semi(exp);


	for (int i = 0; i < expressions.size(); i++)
    	if(validity(expressions[i])) return 0;

	for (int i = 0; i < expressions.size(); i++)
		bonus(expressions[i]);
	
	remove_duplicates();
	cout << endl;
	print();
	cout << endl;
	}
