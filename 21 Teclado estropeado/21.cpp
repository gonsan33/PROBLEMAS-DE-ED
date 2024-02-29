#include <iostream>
#include <string>
#include <iomanip>
#include <list>
using namespace std; 

bool resuelveCasos() {
	string entrada; 
	cin >> entrada; 
	if (!cin) return false; 
	else {
		list<char> sal; 
		auto it = sal.begin(); 


		for (int i = 0; i < entrada.size(); ++i) {
			switch (entrada[i]) {
			case '+':
				it = sal.end();
				break;
			case '-':
				it = sal.begin();
				break;
			case '3':
				if(it!= sal.end()) it = sal.erase(it);
				break;
			case '*':
				if (it != sal.end()) ++it;
				break;
			default:
				it = sal.insert(it, entrada[i]); 
				++it; 
				break;
			}
		}

		for (char& c : sal) cout << c; 
		cout << '\n'; 
		return true; 
	}

}


int main() {
	while (resuelveCasos()); 
	return 0; 
}