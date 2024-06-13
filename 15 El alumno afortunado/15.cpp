#include <iostream>
#include <string>
#include <queue>
using namespace std; 
/*
int resolver(deque<int>& q, int m) {

	if (q.size() == 1) return q.front(); 
	
	for (int i = 0; i < m ; ++i) {
		q.push_back(q.front()); 
		q.pop_front(); 
	}
	q.pop_front(); 
	return resolver(q, m); 
}


bool resuelveCasos() {
	int N, m; 
	cin >> N >> m; 
	if (N == 0 && m == 0) return false; 
	deque<int> q;
	for (int i = 1; i <= N; ++i) q.push_back(i); 
	cout << resolver(q,m) << '\n'; 
	return true; 
}

int main() {
	while (resuelveCasos()); 
	return 0; 
}
*/