#include <iostream> 
#include <deque>
#include <string>
#include <vector>
#include <stack>
using namespace std; 

bool resuelveCasos() {
	string v; 

	getline(cin, v); 
	if (!cin) return false; 
	stack<char> p0, p1; 
	for (int i = 0; i < v.size(); ++i) {
		if (i % 2 == 0) p0.push(v[i]);
		else p1.push(v[i]); 
	}
	deque<char> dq; 
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
		if (prim != 'a' && prim != 'e' && prim != 'i' && prim != 'o' && prim != 'u' && sec != 'a' && sec != 'e' && sec != 'i' && sec != 'o' && sec != 'u' && prim != 'A' && prim != 'E' && prim != 'I' && prim != 'O' && prim != 'U' && sec != 'A' && sec != 'E' && sec != 'I' && sec != 'O' && sec != 'U') {
			dq.push_back(dq.front());
			dq.pop_front();
			dq.push_front(prim);
		}
		else dq.push_back(prim); 
	}
	//Visualizaci�n: 
	while (!dq.empty()) {
		cout << dq.front(); 
		dq.pop_front(); 
	}

	cout << '\n';

	return true;

	return true; 
}

int main() {
	/*
	string v = "AEIOU, borriquito como tu";
	for (int i = 0; i < v.size() - 1; ++i) {
		char prim = v[i];
		char sec = v[i + 1];
		if (prim != 'a' && prim != 'e' && prim != 'i' && prim != 'o' && prim != 'u' && sec != 'a' && sec != 'e' && sec != 'i' && sec != 'o' && sec != 'u' && prim != 'A' && prim != 'E' && prim != 'I' && prim != 'O' && prim != 'U' && sec != 'A' && sec != 'E' && sec != 'I' && sec != 'O' && sec != 'U') {
			char aux = v[i];
			v[i] = v[i + 1];
			v[i + 1] = aux;
			if (i > 0) {
				prim = v[i - 1]; 
				sec = v[i]; 
				if (prim != 'a' && prim != 'e' && prim != 'i' && prim != 'o' && prim != 'u' && sec != 'a' && sec != 'e' && sec != 'i' && sec != 'o' && sec != 'u' && prim != 'A' && prim != 'E' && prim != 'I' && prim != 'O' && prim != 'U' && sec != 'A' && sec != 'E' && sec != 'I' && sec != 'O' && sec != 'U') {
					char aux = v[i-1];
					v[i-1] = v[i ];
					v[i ] = aux;
				}

			}
		}
	}
	int i = 0;
	int j = v.size() - 1;
	string salida;
	while (i < j) {
		salida.push_back(v[i]);
		salida.push_back(v[j]);
		++i;
		--j;
	}
	if (i == j) salida.push_back(v[i]);

	cout << salida;
	*/
	while (resuelveCasos()); 
	return 0; 
}