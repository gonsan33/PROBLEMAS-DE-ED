#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <exception>
#include <fstream>
#include <stdexcept>
using namespace std; 

/*
Todas las operaciones tienen coste constante 
*/
class CarnetPuntos {
public: 
	CarnetPuntos() : v(MAX_PUNTOS+1) {}
	void nuevo(const string& dni) { //O(1)
		if (mapa.count(dni)) throw domain_error("Conductor duplicado"); 
		else {
			mapa[dni] = MAX_PUNTOS;
			++v[MAX_PUNTOS]; 
		}
	}
	
	void quitar(const string& dni, int puntos) { //O(1)
		int& p = buscar_por_dni(dni); 
		--v[p]; 
		p = max(0, p - puntos); 
		++v[p]; 
	}

	int consultar(const string& dni) const { //O(1)
		return buscar_por_dni(dni); 
	}

	int cuantos_con_puntos(int puntos) const { //O(1)
		if (puntos < 0 || puntos > MAX_PUNTOS) throw domain_error("Puntos no validos"); 
		return v[puntos]; 
	}



private: 
	const int MAX_PUNTOS = 15; 
	unordered_map<string, int> mapa; 
	vector<int> v; 

	int& buscar_por_dni(const string& dni)  { //O(1)
		auto it = mapa.find(dni); 
		if (it == mapa.end()) throw domain_error("Conductor inexistente");
		else return it->second; 
		
	}

	const int& buscar_por_dni(const string& dni) const { //O(1)
		auto it = mapa.find(dni);
		if (it == mapa.end()) throw domain_error("Conductor inexistente");
		else return it->second;

	}

};


void consultar(const string& dni, const CarnetPuntos& cp) {
	int a = cp.consultar(dni); 
	cout << "Puntos de " << dni << ':' << ' ' << a << '\n'; 
}

void cuantos_con_puntos(int N, const CarnetPuntos& cp) {
	int a = cp.cuantos_con_puntos(N); 
	cout << "Con " << N << " puntos hay " <<  a << '\n'; 
}

bool resuelveCasos() {
	string primero; 
	CarnetPuntos cp; 
	while (cin >> primero && primero != "FIN") {
		try {
			string segundo;
			cin >> segundo;
			if (primero == "nuevo") {
				cp.nuevo(segundo);
			}
			else if (primero == "cuantos_con_puntos") cuantos_con_puntos(stoi(segundo), cp);
			else if (primero == "consultar") consultar(segundo, cp);
			else if (primero == "quitar") {
				int puntos;
				cin >> puntos;
				cp.quitar(segundo, puntos);
			}
		}
		catch (domain_error& e) {
			cout << "ERROR: " << e.what() << '\n'; 
		}

	}
		
	if (!cin.fail()) cout << "---\n"; 
	return !cin.fail(); 
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCasos()); 
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0; 
}