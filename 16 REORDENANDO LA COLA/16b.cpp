#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std; 

//Coste de la solución O(n), n = número de elementos de la cola inicial

void resolver(queue<int>& q, queue<int> & res) {
	deque<int> dq; 
	while (!q.empty()) {
		int elem = q.front(); 
		q.pop(); 
		if (elem >= 0) dq.push_back(elem);
		else dq.push_front(elem); 
	}
	res = queue<int>(dq); 
}

bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (n == 0) return false; 
	queue<int> q; 
	for (int i = 0; i < n; ++i) {
		int elem; 
		cin >> elem; 
		q.push(elem); 
	}

	queue<int> res; 
	resolver(q,res);
	if (!res.empty()) {
		cout << res.front(); 
		res.pop(); 
	}
	while (!res.empty()) {
		cout << " " << res.front(); 
		res.pop(); 
	}
	cout << '\n'; 
	return true; 
}

int main() {
	while (resuelveCasos()); 
}