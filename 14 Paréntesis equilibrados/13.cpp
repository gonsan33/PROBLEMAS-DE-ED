#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std; 

bool resolver(string& str) {
	bool eq = true; 
	int i = 0; 
	stack<char> st; 
	while (i < str.size() && eq) {
		if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
			st.push(str[i]);
		}
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
			if (!st.empty()) {
				char prev = st.top();
				st.pop();
				eq = (prev == '(' && str[i] == ')') || (prev == '{' && str[i] == '}') || (prev == '[' && str[i] == ']');
			}
			else eq = false; 
		}
		++i; 
	}
	return eq && st.empty(); 
}

bool resuelveCasos() {
	string input; 
	getline(cin, input,'\n');
	if (!cin)  return false; 
	if (resolver(input)) cout << "SI\n";
	else cout << "NO\n"; 
	return true; 

}


int main() {
	while (resuelveCasos()); 
	return 0; 
}