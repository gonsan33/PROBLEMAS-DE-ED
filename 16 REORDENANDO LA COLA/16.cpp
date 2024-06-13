#include <queue>
#include <iostream>
#include <deque>
using namespace std; 

/*
bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (n == 0) return false; 
	queue<int> q; 
	for (int i = 0; i < n; ++i) {
		int aux; 
		cin >> aux; 
		q.push(aux); 
	}
	//Se ordena
	deque<int> dq; 
	for (int i = 0; i < n; ++i) {
		int elem = q.front(); 
		if (elem >= 0) dq.push_back(elem);
		else dq.push_front(elem); 
		q.pop(); 
	}
	//Se copia: 
	for (int i = 0; i < n; ++i) {
		q.push(dq.front()); 
		dq.pop_front(); 
	}
	//Visualización: 
	cout << q.front(); 
	q.pop(); 
	for (int i = 1; i < n; ++i) {
		cout << ' ' << q.front(); 
		q.pop(); 
	}
	cout << '\n'; 

	return true; 
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}
*/