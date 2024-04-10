#include <iostream>
#include <string>
#include <map>
using namespace std; 


bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (n == 0) return false; 
	
	map<string, int> map; 
	pair<string, string> aux; 
	for (int i = 0; i < n; ++i) {
		cin.ignore(1); 
		getline(cin, aux.first); 
		cin >> aux.second; 
		map[aux.first] += (aux.second == "CORRECTO" ? 1 : -1); 
	}
	
	for (pair<string, int> x : map) {
		if (x.second != 0) cout << x.first << ',' << ' ' << x.second << '\n';
	}

	cout << "---\n"; 
	return true; 
}


int main() {
	while (resuelveCasos()); 
	return 00; 
}