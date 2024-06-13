#include "bintree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;

vector<int> primos; 

bool primo(int n) {
	auto it = lower_bound(primos.begin(), primos.end(), n); 
	return it != primos.end() && *it == n; 
}

pair<int, int> barrera(const BinTree<int>& t) { //número, profundidad //O(n), n = nodos árbol 
	//Recorrido en profundidad del árbol 
	queue<pair<BinTree<int>,int>> pending; 
	if (!t.empty()) pending.push({ t,1 });
	BinTree<int> current; 
	int level; 
	bool encontrado = false; 
	while (!pending.empty() && !encontrado) {
		current = pending.front().first; 
		level = pending.front().second; 
		pending.pop(); 
		encontrado = current.root() % 7 == 0 && current.root() != 7; 
		bool prime = primo(current.root()); 
		if (!prime && !current.left().empty()) pending.push({ current.left(), level + 1 });
		if (!prime && !current.right().empty()) pending.push({ current.right(),level + 1 });
	}
	if (encontrado)return { current.root(), level};
	else return { -1,-1 }; 
}




void resuelveCasos() {
	BinTree<int> t = read_tree<int>(cin); 
	auto [elem, prof] = barrera(t); 
	if (prof == -1) cout << "NO HAY\n";
	else cout << elem << ' ' << prof << '\n'; 



}

int main() {
	//Genero primos del 1 al 5.000
	primos.push_back(2); 
	for (int i = 3; i < 5000; ++i) {
		int j = 0; 
		while (j < primos.size() && i % primos[j] != 0) ++j;
		if (j == primos.size()) primos.push_back(i); 
	}

	int N; 
	cin >> N; 
	for (int i = 0; i < N; ++i) resuelveCasos(); 
	return 0; 
}