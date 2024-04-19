#include <map>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std; 

class comparador {
public: 

	bool operator() (const pair<string, int>& a, const pair<string, int>& b) { // da a > b
		return a.second > b.second || (a.second == b.second && a.first < b.first); 
	}

};

bool resuelveCasos() {
	string primero; 
	unordered_map<string, string> m; //clave : persona, valor : deporte
	unordered_set<string> bannedKeys; //claves que no pueden estar en el mapa
	string deporte; 
	map<string, int>  mapa_deportes; //clave: deporte, valor: número de personas que practican el deporte 
	while (cin >> primero && primero != "_FIN_") {
		if (isupper(primero[0])) { //es un deporte
			deporte = primero; 
			mapa_deportes[deporte] = 0; 
		}
		else { //es una persona que se apunta al deporte deporte 
			string & persona = primero; 
			if (m.count(persona) && m.at(persona) != deporte) { //hay que quitarlo, se ha apuntado a dos deportes
				--mapa_deportes[m.at(persona)];
				m.erase(persona); 
				bannedKeys.insert(persona); 
			}
			else if (!bannedKeys.count(persona) && !(m.count(persona) && m.at(persona) == deporte)) {
				++mapa_deportes[deporte]; 
				m[persona] = deporte; 
			}

		}
	}

	if (!cin.fail()) {
		//cojo un vector y lo ordeno
		vector<pair<string, int>> v(mapa_deportes.size()); 
		int i = 0; 
		for (auto& [dep, n] : mapa_deportes) {
			v[i] = { dep,n }; 
			++i; 
		}

		std::sort(v.begin(), v.end(), comparador());

		for (const auto& [dep, n] : v) {
			cout << dep << ' ' << n << '\n'; 
		}

		cout << "---\n"; 
	}

	return !cin.fail(); 
}


int main() {
	while (resuelveCasos()); 
	return 0; 
}