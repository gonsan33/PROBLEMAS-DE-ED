#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
using namespace std; 


bool resuelveCasos() {
	stack<char> st; 
	string line; 
	getline(cin, line,'\n');
	if (!cin) return false; 
	auto it = line.begin(); 
	bool equilibrado = true; 
	while (it != line.end() && equilibrado) {
		char c = *it; 
		if (c == '(' || c == '[' || c == '{') st.push(c);
		else if (c == ')' || c == ']' || c == '}') {
			equilibrado = !st.empty() && (st.top() == '(' && c == ')' || st.top() == '[' && c == ']' || st.top() == '{' && c == '}');
			if(!st.empty())st.pop(); 
		}
		++it; 
	}

	if (equilibrado) cout << "SI\n";
	else cout << "NO\n"; 

	return true; 


}

int main() {
	while (resuelveCasos()); 
	return 0; 
}