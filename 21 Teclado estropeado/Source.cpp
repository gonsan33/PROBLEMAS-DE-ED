#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
using namespace std; 

bool resuelveCasos() {
	deque<char> dq; 
	stack<char> st; 
	string str; 
	cin >> str;
	if (!cin) return false; 
	for (int i = 0; i < str.size(); ++i) {
		switch (str[i]) {
		case '-': 
			while (!st.empty()) {
				dq.push_front(st.top()); 
				st.pop(); 
			}
			break; 

		case '+': 
			while (!dq.empty()) {
				st.push(dq.front()); 
				dq.pop_front(); 
			}
			break; 
		case '*': 
			if (!dq.empty()) {
				st.push(dq.front());
				dq.pop_front();
			}
			
			break; 
		case '3': 
			if(!dq.empty())dq.pop_front(); 
			break; 
		default: //letra
			while (!dq.empty()) {
				st.push(dq.front());
				dq.pop_front();
			}
			dq.push_front(str[i]);
			
			break; 
		}
	}
	while (!st.empty()) {
		dq.push_front(st.top());
		st.pop();
	}
	while (!dq.empty()) {
		cout << dq.front() << ' '; 
		dq.pop_front(); 
	}
	cout << '\n'; 
	return true;	
}


int main() {
	while (resuelveCasos()); 
	return 0; 
}