// Problema iterativo
// Eliminar de un vector todos los números impares, con coste lineal

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <utility>
#include <cstdlib>
#include <set>



// P = { n >= 0 && v = V && n = N && ord(v,n) && forall i : 0 <= i < n: v[i] > 0}
// donde ord(v,k) = {forAll i : 0 <= i < k-1 : v[i] < v[i + 1] }
// proc quitaImpares (inout int v [], inout int n);
// Q = { ord(v,n) && forAll i : 0 <= i < n : v[i] % 2 == 0 &&
// n = # i : 0 <= i < N : V[i] % 2 == 0 &&
// forAll i : 0 <= i < n : (existe j : 0 <= j < N : v[i] = V[j] }

// Invariante : {ord(v,pares) && forAll i : 0 <= i < pares : v[i] % 2 == 0 &&
//               forAll i : 0 <= i < pares : (existe j : 0 <= j < N : v[i] = V[j] &&
//               pares = # i : 0 <= i < k : V[i] % 2 == 0 && 0 <= k < N }

// cota : n - k
// Coste O(n) siendo n el número de elementos del vector. El programa tiene un bucle que recorre los n elementos y el coste de cada vuelta del bucle es constante.
void resolver (std::vector<int> & v) {
    int k = 0; int pares = 0;
    while (k < v.size()) {
        if (v[k] % 2 == 0){
            v[pares] = v[k];
            ++pares;
        }
        ++k;
    }
    v.resize(pares);
}

bool resuelveCaso() {
    int numElem;
    std::cin >> numElem;
    if (numElem == -1) return false;
    std::vector<int> v(numElem);
    for (int i = 0; i < numElem; ++i) {
        std::cin >> v[i];
    }
    resolver(v);
    for (int i = 0; i < v.size(); ++i)
    std::cout << v[i] << ' ';
    std::cout << '\n';
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
/*#ifndef DOMJUDGE
    std::ifstream in("/Users/isabel/Dropbox/XcodePrograms/Prueba/datos1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
*/
    
    while (resuelveCaso())
    ;
    
    // Para restablecer entrada. Comentar para acepta el reto
/*
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
*/
    return 0;
}