#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <iomanip>
#include <stack>
#include <list>
using namespace std; 

void X2toX1(deque<char>& dq, const string& str) {
	int i = 0; 
	bool izq = true; 
	stack<char> st1; 
	stack<char> st2; 
	while (i < str.size() ) {
		if (izq) {
			st1.push(str[i]);
			++i;
			izq = false; 
		}
		else {
			st2.push(str[i]);
			++i; 
			izq = true; 
		}

	}
	while (!st1.empty()) {
		dq.push_front(st1.top()); 
		st1.pop(); 
	}
	while (!st2.empty()) {
		dq.push_back(st2.top());
		st2.pop();
	}
}
bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'; 
}

void invertir(int ini, int fin, string& str, stack<char>& acum) {
	for (int i = ini; i < fin; ++i) {
		str[i] = acum.top(); 
		acum.pop(); 
	}
}


void X1toX(string& str) {
	//segmento más largo de no vocales 
	int i = 0; 
	int j = 0; 
	stack<char> acum; 
	while (j < str.size()) {
		if (!isVowel(str[j])) {
			acum.push(str[j]); 
		}
		else {
			invertir(i, j, str, acum); 
			i = j + 1; 
		}
		++j; 
	}

	//si la última es una vocal, invierto 
	if (!isVowel(str[--j])) invertir(i, j+1, str, acum); 
}

bool resuelveCasos() {
	string line; 
	getline(cin, line, '\n'); 
	if (!cin) return false; 

	deque<char> dq; 
	X2toX1(dq,line);
	for (int i = 0; i < line.size(); ++i) {
		line[i] = dq.front(); 
		dq.pop_front(); 
	}
	X1toX(line); 
	cout << line << '\n'; 
	return true; 
}


int main() {
	while (resuelveCasos()); 
	return 0; 
}