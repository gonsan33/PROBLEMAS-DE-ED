#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <vector>
using namespace std; 

void resolver(const vector<int>& v, int k) {
	deque<pair<int, int>> dq;

	dq.push_back({ -1,-1 }); //primer valor para comparar
	for (int i = 0; i < k; ++i) {
		if (v[i] >= dq.front().first) {
			dq.clear(); 
			dq.push_back({ v[i], i }); 
		}
		else {
			while (!dq.empty() && v[i] >= dq.back().first) {
				dq.pop_back(); 
			}
			dq.push_back({ v[i], i }); 
		}		
	}
	cout << dq.front().first; 
	for (int j = 0; j < v.size() - k; ++j) {
		//Miro si tengo que sacar el primer elemento: 
		if (dq.front().second <= j) dq.pop_front(); 

		//Incorporo el nuevo elemento: 
		if (v[j+k] >= dq.front().first) {
			dq.clear();
			dq.push_back({ v[j+k], j+k });
		}
		else {
			while (!dq.empty() && v[j+k] >= dq.back().first) {
				dq.pop_back();
			}
			dq.push_back({ v[j+k], j+k });
		}
		cout << ' ' << dq.front().first; 

	}

}


bool resuelveCasos() {
	int n, k; 
	cin >> n; 
	if (!cin) return false; 
	cin >> k; 
	vector<int> v(n); 
	for (auto& x : v) cin >> x; 
	resolver(v,k); 
	return true; 

}


int main() {
	while (resuelveCasos()); 
	return 0; 
}