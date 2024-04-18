#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

bool resuelveCasos() {
	int n;
	cin >> n;
	if (n == 0) return false; 
	
	unordered_map<int, vector<string>> lo_tienen; 
	unordered_map<string, int> sin_tachar; 

	//leer cartones 
	for (int i = 0; i < n; ++i) {
		string nombre; 
		cin >> nombre; 
		int& cuantos = sin_tachar[nombre]; 
		int num; 
		while (cin >> num, num != 0) {
			++cuantos; 
			lo_tienen[num].push_back(nombre); 
		}
	}


	//se empieza a jugar
	set<string> ganadores; 
	while (ganadores.empty()) { //no hay ganadores 
		int num; 
		cin >> num; 
		for (auto j : lo_tienen[num]) {
			--sin_tachar[j]; 
			if (sin_tachar[j] == 0) ganadores.insert(j); 
		}
	}

	//se imprimen ganadores 
	for (const string& str : ganadores) {
		cout << str << ' '; 
	}
	cout << '\n'; 

	return true; 


	//coste 
	/*
	N jugadores 
	M número total de números en los cartones 
	B números que salen del bombo 
	G número de ganadores  G <= N 
	
	leer cartones O(N+M) 
	jugar O(B+M+G log G) 
	sacar por pantalla O(G) 
	luego, al final O(B+N+ G log G) 

	
	*/
}


int main() {
	while( resuelveCasos());
	return 0;
}