#include <iostream>
#include <stack>
#include <vector>
using namespace std; 

bool resuelveCasos() {
	int n; 
	cin >> n; 
	if (!cin) return false; 
	vector<int> v(n); 
	for (auto& x : v) cin >> x; 

	stack<int> primero; 
	stack<int> segundo; 
	stack<int> tercero; 
	primero.push(v[0]); 
	bool pierde = false; 
	for (int i = 1; i < v.size() && !pierde; ++i) {
		if (v[i] < primero.top()) primero.push(v[i]);
		else if (segundo.empty() || v[i] > segundo.top()) segundo.push(v[i]);
		else {
			tercero.push(v[i]);
			pierde = true; 
		}
	}
	if (pierde) cout << "ELEGIR OTRA\n";
	else cout << "SIEMPRE PREMIO\n"; 
	return true; 

}

int main() {
	while (resuelveCasos()); 
	return 0; 
}