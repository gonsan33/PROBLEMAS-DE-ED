#include <iostream>
#include <unordered_map> 
#include <map>
#include <unordered_set> 
#include <set>
#include <list>
#include <vector>
#include <string>
#include <fstream>
using namespace std; 

class Autoescuela {


private: 
	using Alumno = string; 
	using Profesor = string; 
	struct InfoAlumno {
		string nombre; 
		string profesor; 
		int puntos; 
	}; 
	
	unordered_map < Profesor, set<Alumno>> mapa_prof;
	unordered_map<Alumno,InfoAlumno> alumnos; 

	InfoAlumno& buscar_alumno(const Alumno& a) {
		auto it = alumnos.find(a); 
		if (it == alumnos.end()) throw domain_error("El alumno " + a + " no está matriculado");
		else return it->second; 
	}

	const InfoAlumno& buscar_alumno(const Alumno& a)const  {
		auto it = alumnos.find(a);
		if (it == alumnos.end()) throw domain_error("El alumno " + a + " no está matriculado");
		else return it->second;
	}

	set<Alumno>& buscar_alumnos_de_profesor(const Profesor& p) { //O(1)
		auto it = mapa_prof.find(p);
		if (it == mapa_prof.end()) return mapa_prof[p]; 
		else return it->second;
	}



public:
	Autoescuela() : mapa_prof(), alumnos() {}
	void alta(const Alumno& a, const Profesor& p) { //coste O(log A), donde A es el número máximo de alumnos por Profesor
		//miro si está matriculado en la autoescuela 
		auto it = alumnos.find(a);
		if (it != alumnos.end()) {
			//le quito el alumno a su profesor
			mapa_prof.at(it->second.profesor).erase(a);

			it->second.profesor = p;
		}
		else {
			InfoAlumno rta; 
			rta.nombre = a; 
			rta.profesor = p; 
			rta.puntos = 0; 
			alumnos[a] = rta;

		}

		//se lo añado al nuevo profesor: 
		buscar_alumnos_de_profesor(p).insert(a);
	}

	bool es_alumno(const Alumno& a, const Profesor& p) const { //O(1)
		return mapa_prof.count(p) &&  mapa_prof.at(p).count(a); 
	}

	int puntuacion(const Alumno& a) const { //O(1)
		return buscar_alumno(a).puntos; 
	}

	void actualizar(const Alumno& a, int N) { //O(1)
		int& puntos = buscar_alumno(a).puntos; 
		puntos += N; 
	}

	vector<Alumno> examen(const Profesor& p, int N)  { //O(A) donde A es el número máximo de alumnos por Profesor
		vector<Alumno> v; 
		const set<Alumno>& s = buscar_alumnos_de_profesor(p); 
		for (const Alumno& a : s) {
			if (alumnos.at(a).puntos >= N) v.push_back(a); 
		}
		return v; 
	}

	void aprobar(const Alumno& a) {
		InfoAlumno& info = buscar_alumno(a); 
		mapa_prof.at(info.profesor).erase(a); 
		alumnos.erase(a); 
	}

};

void es_alumno(const string& a, const string& p, const Autoescuela& autoescuela) {
	if (autoescuela.es_alumno(a, p)) cout << a << " es alumno de " << p << '\n'; 
	else cout << a << " no es alumno de " << p << '\n';
}

void puntuacion(const string& a, const Autoescuela& autoescuela) {
	int p = autoescuela.puntuacion(a);
	cout << "Puntuacion de " << a << ": " << p << '\n';
}

void examen(const string& p, int N, Autoescuela& autoescuela) {
	const vector<string>& v = autoescuela.examen(p, N);

	cout << "Alumnos de " << p << " a examen: \n"; 
	for (const auto& x : v) {
		cout << x << '\n';
	}

}

bool resuelveCasos() {
	string primero;
	Autoescuela autoescuela;
	while (cin >> primero && primero != "FIN") {
		try {
			string segundo;
			cin >> segundo;
			if (primero == "alta") {
				string tercero;
				cin >> tercero; 
				autoescuela.alta(segundo, tercero); 
			}
			else if (primero == "es_alumno") {
				string tercero;
				cin >> tercero;
				es_alumno(segundo, tercero, autoescuela);
			}
			else if (primero == "actualizar") {
				string tercero;
				cin >> tercero;
				autoescuela.actualizar(segundo, stoi(tercero)); 
			}
			else if (primero == "puntuacion") {
				puntuacion(segundo, autoescuela); 
			}
			else if (primero == "examen") {
				int tercero; 
				cin >> tercero; 
				examen(segundo, tercero, autoescuela); 
			}
			else if (primero == "aprobar") {
				autoescuela.aprobar(segundo); 
			}
		}
		catch (domain_error& e) {
			cout << "ERROR\n";
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