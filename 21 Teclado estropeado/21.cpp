#include <iostream>
#include <string>
#include <iomanip>
using namespace std; 

bool resuelveCasos() {
	string str; 
	string entrada; 
	cin >> entrada; 
	if (!cin) return false; 
	else {
		auto it = str.begin(); 

		for (int i = 0; i < entrada.size(); ++i) {
			switch (entrada[i]) {
			case '+':
				it = str.end();
				break;
			case '-':
				it = str.begin();
				break;
			case '3':
				it = str.erase(it);
				break;
			case '*':
				if (it != str.end()) ++it;
				break;
			default:
				it = str.insert(it, entrada[i]); 
				++it; 
				break;
			}
		}

		for (char& c : str) cout << c; 
		cout << '\n'; 
		return true; 
	}

}


int main() {
	while (resuelveCasos()); 
	return 0; 
}