#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std; 

void resuelveCasos() {
	int n; 
	cin >> n; 
	vector<int> v(n); 
	for (auto& x : v) cin >> n; 

	int ini = 0; 
	int lmax = 0; 

	unordered_map<int, int> map; //elemento, posición en el vector
	//coste lineal en los elementos del vector
	for (int i = 0; i < v.size(); ++i) {
		if (map.count(v[i]) && map[v[i]] >= ini) {
			ini = map[v[i]] + 1; 
		}
		lmax = max(lmax, i - ini + 1); 
	}

	cout << lmax << '\n'; 
}


int main() {
	int n; 
	cin >> n; 
	for (int i = 0; i < n; ++i) resuelveCasos(); 
	return 0; 
}