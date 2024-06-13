#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std; 


int resolver(deque<int> & dq, int s) {
	while (dq.size() > 1) {
		for (int i = 0; i < s; ++i) {
			dq.push_back(dq.front()); 
			dq.pop_front(); 
		}
		dq.pop_front(); 
	}
	return dq.front(); 
}

bool resuelveCasos() {
	int n, s; 
	cin >> n >> s; 
	if (n == 0 && s == 0) return false; 
	deque<int> dq; 
	for (int i = 1; i <= n; ++i) dq.push_back(i); 
	cout << resolver(dq, s) << '\n';

	return true; 
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}