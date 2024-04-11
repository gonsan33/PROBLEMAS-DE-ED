#include <iostream>
#include <string>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

void tolower(string& palabra) {
	for (char& c : palabra) {
		c = tolower(c);
	}
}

bool resuelveCasos() {
	int n;
	cin >> n;
	if (n == 0) return false;

	string str; 
	cin.ignore(1); 

	map<string, vector<int>> map; 

	for (int i = 0; i < n; ++i) {
		//leo la l�nea 
		getline(cin, str); 

		//lo paso a un stringstream 
		stringstream ss = stringstream(str); 

		//proceso cada palabra de la l�nea: 
		while (!ss.eof()) {
			string palabra;
			ss >> palabra; 
			tolower(palabra); 
			vector<int>& v = map[palabra]; 
			if (v.empty() || v.back() != i+1) v.push_back(i + 1); 
			//if (!map.count(palabra) || map[palabra][map[palabra].size() - 1] != i + 1)  map[palabra].push_back(i + 1);  //esto est� mal, map[palabra] tiene coste logar�tmico, llamo varias veces...
		}
	}

	for (auto const & [palabra, v] : map) { //const & es para no hacer copias del vector 
		if (palabra.size() > 2) {
			cout << palabra;
			for (auto x : v) cout << " " << x;
			cout << '\n';
		}
		
	}

	cout << "---\n"; 
	

	return true;
}


int main() {
	while (resuelveCasos());
	return 00;
}