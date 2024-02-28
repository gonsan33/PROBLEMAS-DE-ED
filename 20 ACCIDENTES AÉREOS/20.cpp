#include <iostream>
#include <deque>
#include <vector>
#include <fstream>
using namespace std; 


void resolver(const vector<pair<string, int>>& v) {
	deque<pair<string,int>> dq;
	int max = -1; 
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].second >= max) {
			dq.clear(); 
			dq.push_front(v[i]); 
			max = v[i].second; 
			cout << "NO HAY\n"; 
		}
		else {
			//hay que buscarla y la cola no está vacía
			dq.push_back(v[i]); 
			while (dq.front().second <= v[i].second) {
				dq.pop_front(); 
			}
			cout << dq.front().first  << '\n'; 
			dq.push_front(v[i]); 
		}
	}
	cout << "---\n"; 
}


bool resuelveCasos() {
	int N;
	cin >> N;
	if (!cin)
		return false;
	vector<pair<string, int>> v(N); 
	for (int i = 0; i < N; ++i) {
		cin >> v[i].first >> v[i].second; 
	}
	resolver(v); 
	return true;
}






/*
bool resuelveCasos() {
	int n;
	cin >> n;
	if (!cin) return false;
	stack<pair<string, int>> st;
	int max = -1;
	for (int i = 0; i < n; ++i) {
		pair<string, int> lectura;
		cin >> lectura.first >> lectura.second;
		if (lectura.second >= max) {
			while (!st.empty()) st.pop();
			max = lectura.second;
			st.push(lectura);
			cout << "NO HAY\n";
		}
		else {
			stack<pair<string, int>> aux;
			while (!st.empty() && lectura.second >= st.top().second) {
				aux.push(st.top());
				st.pop();
			}
			if (!st.empty()) cout << st.top().first << ' ' << st.top().second << '\n';
			while (!aux.empty()) {
				st.push(aux.top());
				aux.pop();
			}
			st.push(lectura);
			}
	}
	cout << "---\n";
	return true;
}


*/

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCasos()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}