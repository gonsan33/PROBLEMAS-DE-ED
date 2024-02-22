#include <iostream> 
#include <deque>
#include <string>
#include <vector>
#include <stack>
using namespace std; 

bool resuelveCasos() {
	vector<int> v; 

	char aux; 
	cin >> aux; 
	if (!cin) return false; 
	while (aux != '\n') {
		v.push_back(aux);
		cin.get(aux); 
	}

	stack<int> p0, p1; 
	for (int i = 0; i < v.size(); ++i) {
		if (i % 2 == 0) p0.push(v[i]);
		else p1.push(v[i]); 
	}
	deque<int> dq; 
	while (!p0.empty()) {
		dq.push_front(p0.top()); 
		p0.pop(); 
	}
	while (!p1.empty()) {
		dq.push_back(p1.top());
		p1.pop();
	}

	//orden de consonantes 
	for (int i = 0; i < v.size(); ++i) {
		char prim = dq.front(); 
		dq.pop_front(); 
		char sec = dq.front(); 
		if (prim != 'a' && prim != 'e' && prim != 'i' && prim != 'o' && prim != 'u' && sec != 'a' && sec != 'e' && sec != 'i' && sec != 'o' && sec != 'u') {
			dq.push_back(dq.front());
			dq.pop_front();
			dq.push_front(prim);
		}
		else dq.push_back(prim); 
	}
	//Visualizaci�n: 
	cout << dq.front();
	dq.pop_back();
	for (int i = 1; i < v.size(); ++i) {
		cout << ' ' << dq.front();
		dq.pop_back();
	}
	cout << '\n';

	return true;

	return true; 
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}