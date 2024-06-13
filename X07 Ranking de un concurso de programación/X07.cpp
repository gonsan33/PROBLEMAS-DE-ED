#include <set>
#include <iostream>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include <fstream>
using namespace std; 


class Concurso {
	using Problema = string;
	using Equipo = string; 
private: 
	
	struct InfoEquipo {
		Equipo nombre; 
		int resueltos; 
		set<InfoEquipo>::iterator it; 
		long long int tiempo; 

		bool operator < (const InfoEquipo& a) const {
			return this->resueltos < a.resueltos || this->resueltos == a.resueltos && this->tiempo > a.tiempo
				|| this->resueltos == a.resueltos && this->tiempo == a.tiempo && this->nombre > a.nombre; 
		}
	};

	struct ProblemaEquipo {
		int envios_erroneos; 
		bool resuelto; 
	};

	using InfoProblema = unordered_map<Equipo, ProblemaEquipo>; 

	unordered_map<Equipo, InfoEquipo> equipos; 
	unordered_map<Problema, InfoProblema> problemas; 
	set<InfoEquipo> clasification; 


public: 

	void registrarVeredicto(const Equipo& equipo, const Problema& problema, long long int tiempo, const string& veredicto) {
		
		auto it_equipos = equipos.find(equipo); 
		//Miro si el equipo está registrado

		if (it_equipos == equipos.end() && veredicto == "AC") { //Registro el equipo  
			InfoEquipo registro;
			registro.nombre = equipo; 
			registro.resueltos = 1; 
			registro.tiempo = tiempo; 
			registro.it = clasification.insert(registro).first; 
			problemas[problema][equipo] = ProblemaEquipo{ 0,true }; 
			equipos[equipo] = registro; 
		}
		else if (it_equipos == equipos.end() && veredicto != "AC") { //Registro el equipo  
			InfoEquipo registro;
			registro.nombre = equipo;
			registro.resueltos = 0;
			registro.tiempo = 0;
			registro.it = clasification.insert(registro).first;
			problemas[problema][equipo] = ProblemaEquipo{ 1,false};
			equipos[equipo] = registro;
		}
		else if (it_equipos != equipos.end() && veredicto != "AC") {
			ProblemaEquipo& probeq = problemas[problema][equipo]; 
			if (!probeq.resuelto) probeq.envios_erroneos += 1; 
		}
		else {
			ProblemaEquipo& probeq = problemas[problema][equipo];
			if (!probeq.resuelto) {
				probeq.resuelto = true; 
				InfoEquipo& infoeq = equipos[equipo]; 
				clasification.erase(infoeq.it); 
				infoeq.resueltos += 1; 
				infoeq.tiempo += 20 * probeq.envios_erroneos + tiempo; 
				infoeq.it = clasification.insert(infoeq).first; 
			}
		}
	}

	vector<string> posiciones() const{
		vector<string> sol; 
		for (const InfoEquipo& infoeq : clasification) {
			sol.push_back(infoeq.nombre + " " + to_string(infoeq.resueltos) + " " + to_string(infoeq.tiempo)); 
		}
		return sol; 
	}



};

void resuelveCasos() {
	Concurso concurso; 
	string nombre; 
	while (cin >> nombre, nombre != "FIN") {
		string prob; 
		long long int tiempo; 
		string veredicto; 
		cin >> prob >> tiempo >> veredicto; 
		concurso.registrarVeredicto(nombre, prob, tiempo, veredicto); 
	}
	vector<string> v = concurso.posiciones(); 
	for (auto it = v.rbegin(); it != v.rend(); ++it) cout << *it << '\n';
	cout << "---\n"; 
}

int main() {
#ifndef DOMJUDGE
std::ifstream in("casos.txt");
auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int n; 
	cin >> n; 
	for (int i = 0; i < n; ++i) resuelveCasos(); 
#ifndef DOMJUDGE
std::cin.rdbuf(cinbuf);
system("PAUSE");
#endif
	return 0; 
}