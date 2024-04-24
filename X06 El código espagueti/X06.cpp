#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <forward_list>
#include <iomanip>
#include <fstream>
using namespace std; 


bool ejecutarSim(map<int,pair<string,string>>& map_instr, map<string, int>& map_var, int N) {
	bool resultado = true; //devuelve true si acaba la simulación, false en otro caso (si hay error)
	auto it = map_instr.cbegin(); 
	int n = 0; 
	while (it != map_instr.cend() && resultado && n <N ) {
		//Cojo la instrucción: 
		auto [instr, variable_o_entero] = it->second; 
		if (instr == "INCR") {
			++map_var[variable_o_entero]; 
			++it; 
		}
		if (instr == "GOTO") {
			int line = stoi(variable_o_entero); 
			it = map_instr.find(line); 
			if (it == map_instr.end() || it == map_instr.cend()) resultado = false; 
		}
		++n; 
	}
	return resultado; 
}

bool resuelveCasos() {
	string primero; 
	map<int, pair<string, string>> map_instr; 
	map<string, int> map_var; 
	int N;
	while (cin >> primero && primero != "BYE") {
		
		if (primero == "RUN") {
			cin >> N; 
			if (ejecutarSim(map_instr, map_var, N)) {
				for (const auto& [key, value] : map_var) {
					cout << key << " = " << value << '\n';
				}
				cout << "OK\n";
			}
			else cout << "ERROR\n"; 

			map_var.clear(); 
		}
		else {
			string & line = primero; 
			string instruction; 
			cin >> instruction; 
			string argument; 
			cin >> argument; 
			map_instr[stoi(line)] = { instruction, argument }; 

		}
	}
	if(!cin.fail())cout << "---\n"; 
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