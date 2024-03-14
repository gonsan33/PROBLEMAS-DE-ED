#include "bintree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std; 

void resuelveCasos(vector<bool>const & es_primo) {
	BinTree<int> t; 
	t = read_tree<int>(cin); 
	queue<pair<BinTree<int>, int >> q; 
	if (!t.empty() && !es_primo[t.root()]) q.push({ t, 1 }); 

	bool encontrado = false; 
	pair<int, int> sol; 
	while (!q.empty() && !encontrado) {
		BinTree<int> current = q.front().first; 
		int nivel = q.front().second; 
		q.pop(); 
		if (current.root() % 7 == 0) {
			encontrado = true;
			sol = { current.root(), nivel };

		}
		if (!current.left().empty() && !es_primo[current.left().root()]) q.push({ current.left(), nivel + 1 }); 
		if (!current.right().empty() && !es_primo[current.right().root()]) q.push({ current.right(), nivel + 1 });
	}
	if (!encontrado) cout << "NO HAY\n";
	else cout << sol.first << ' ' << sol.second << '\n'; 
}


int main() {
	int n; 
	cin >> n; 
	vector<bool> es_primo(5001,false); 
	es_primo[2] = true; 
	for (int i = 3; i < es_primo.size(); ++i) {
		int j = 2; 
		while (j < i && (!es_primo[j] || i % j != 0)) {
			++j; 
		}
		es_primo[i] = j == i ||(j < i  && i% j != 0); 
	}

	for (int i = 0; i < n; ++i) resuelveCasos(es_primo); 
	return 0; 

}