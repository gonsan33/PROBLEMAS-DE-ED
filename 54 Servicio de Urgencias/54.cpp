#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <exception>
#include <stdexcept>
#include <set>
#include <fstream>
using namespace std; 

class Urgencias {
private:
	using Paciente = string;
	using Gravedad = int;
	struct InfoPaciente {
		Gravedad gravedad; 
		list<Paciente>::iterator it; 
	};
	vector<list<Paciente>> gravedades = vector<list<Paciente>>(3);
	unordered_map<Paciente, InfoPaciente> pacientes;
	set<Paciente> recovered;

public: 
	void nuevo_paciente(const Paciente& paciente, Gravedad gravedad) {
		if (pacientes.count(paciente)) throw domain_error("Paciente repetido"); 
		if (gravedad <= 0 || gravedad > 3) throw domain_error("Gravedad incorrecta"); 

		pacientes[paciente].gravedad = gravedad;
		pacientes[paciente].it = gravedades[gravedad-1].insert(gravedades[gravedad-1].cend(), paciente);

	}

	Gravedad gravedad_actual(const Paciente& paciente) const {
		auto it = pacientes.find(paciente); 
		if (it == pacientes.end()) throw domain_error("Paciente inexistente");
		else return it->second.gravedad; 
	}

	Paciente siguiente() {
		Paciente rta; 
		if (!gravedades[2].empty()) {
			rta = gravedades[2].front();
			gravedades[2].pop_front();
		}
		else if (!gravedades[1].empty()) {
			rta = gravedades[1].front();
			gravedades[1].pop_front();
		}
		else if (!gravedades[0].empty()) {
			rta = gravedades[0].front();
			gravedades[0].pop_front();
		}
		else throw domain_error("No hay pacientes"); 
		pacientes.erase(rta); 
		return rta; 
	}

	void mejora(Paciente& paciente) {
		auto it = pacientes.find(paciente);
		if (it == pacientes.end()) throw domain_error("Paciente inexistente");
		else {
			it->second.gravedad--; 
			//Saco el paciente de la lista de la gravedad anterior y lo pongo donde corresponde: 
			gravedades[it->second.gravedad].erase(it->second.it); 
			if (it->second.gravedad > 0)it->second.it = gravedades[it->second.gravedad-1].insert(gravedades[it->second.gravedad-1].begin(), paciente);
			else {
				recovered.insert(paciente);
				pacientes.erase(paciente); 
			}
		}
	}

	vector<Paciente> recuperados() const {
		vector<Paciente> rta;
		for (const Paciente& p : recovered) rta.push_back(p);
		return rta;
	}
};

bool resuelveCasos() {
	string instr; 
	Urgencias urg; 
	cin >> instr; 
	if (!cin) return false; 
	while (instr != "FIN") {
		try {
			if (instr == "nuevo_paciente") {
				string nombre;
				int grav;
				cin >> nombre >> grav;
				urg.nuevo_paciente(nombre, grav);
			}
			else if (instr == "mejora") {
				string nombre;
				cin >> nombre;
				urg.mejora(nombre);
			}
			else if (instr == "gravedad_actual") {
				string nombre;
				cin >> nombre;
				int grav = urg.gravedad_actual(nombre);
				cout << "La gravedad de " << nombre << " es " << grav;
				cout << '\n';

			}
			else if (instr == "siguiente") {
				string nombre = urg.siguiente();
				cout << "Siguiente paciente: " << nombre;
				cout << '\n';

			}
			else { //recuperados 
				vector<string> v = urg.recuperados();
				cout << "Lista de recuperados:";
				for (const string& s : v) cout << " " << s;
				cout << '\n';



			}
		}
		catch (domain_error& e) {
			cout << "ERROR: " << e.what(); 

			cout << '\n';

		}
		

		cin >> instr; 
	}

	cout << "---\n"; 
	return true; 
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.in");
	std::ofstream out("output.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = cout.rdbuf(out.rdbuf()); 
#endif
	while (resuelveCasos()); 
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf); 
#endif
	return 0; 
}