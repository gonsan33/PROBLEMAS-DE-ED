#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
using namespace std; 

void leer(map<string, int>& map) {
	string str; 
	getline(cin, str); 
	stringstream ss(str); 
	string clave; 
	int val; 
	while (ss >> clave >> val) {
		map.insert({ clave, val }); 
	}
}

class Comparator {
public : 
	bool operator() (char a, char b) const {
		if (a == '+')  return b == '-' || b == '*';
		else if (a == '-') return b == '*' ; 
		if (a == '*') return false; 
	}
};

void resolver(map<string, int>& antiguo, map<string, int>& nuevo) {
	map<char, vector<string>, Comparator> rta; 
	auto itAnt = antiguo.begin(); 
	auto itN = nuevo.begin(); 

	while (itAnt != antiguo.end() && itN != nuevo.end()) {
		
		auto [keyAnt, valAnt] = *itAnt; 
		auto [keyN, valN] = *itN;

		if (keyAnt < keyN) { //no voy a encontrar keyAnt en el nuevo diccionario 
			rta['-'].push_back(keyAnt);
			++itAnt; 
		}
		else if (keyAnt == keyN && valAnt != valN) {
			rta['*'].push_back(keyAnt);
			++itAnt; 
			++itN; 
		}
		else if (keyN < keyAnt) {
			rta['+'].push_back(keyN); 
			++itN ; 
		}
		else {
			++itAnt; 
			++itN; 
		}
	}

	while (itAnt != antiguo.end()) {
		auto [keyAnt, valAnt] = *itAnt;
		rta['-'].push_back(keyAnt);
		++itAnt;
	}
	while (itN!= nuevo.end()) {
		auto [keyN, valN] = *itN;
		rta['+'].push_back(keyN);
		++itN;
	}

	if (rta.empty()) cout << "Sin cambios\n"; 
	else {
		for (auto& [c, v] : rta) {
			if (!v.empty()) {
				cout << c; 
				for (auto& x : v) cout << ' ' << x; 
				cout << '\n'; 
			}
		}
	}
	cout << "---\n"; 

	

}


void resuelveCasos() {
	map<string, int> antiguo; 
	map<string, int> nuevo;
	leer(antiguo); 
	leer(nuevo); 

	resolver(antiguo, nuevo); 
}

int main() {
	int n; 
	cin >> n; 
	cin.ignore(1); 
	for (int i = 0; i < n; ++i) resuelveCasos(); 
	return 0; 
}