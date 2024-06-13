// Ejercicio iterativo
// Se tiene un vector con \emph{k $>$ 0} valores enteros diferentes. Cada valor
// se encuentra repetido $k_i$ veces, siendo consecutivos todos los valores
// iguales del vector. Se pide encontrar el número de valores distintos.

// Tecnica de divide y vencerás.
// Casos base: Un elemento, dos elementos y que coincida el valor de los dos
// extremos del vector
// Caso recursivo: Se compara el elemento central con los dos que
// tiene a cada lado para intentar optimizar un poco.
// Si es distinto de los dos de los lados, se hacen llamadas recursivas a cada lado y se suma 1.
// Si es igual que el del lado derecho se hacen las dos llamadas recursivas a cada lado pero no se suma 1.
// Si tiene el mismo valor a cada lado, se hacen las dos llamadas recursivas y se resta 1, ya que se contará el mismo intervalo en los dos lados.
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

int resolver (std::vector <int> & v, int ini, int fin) {
    if (ini == fin) return 1; // Vector 1 elemento
    else if (ini + 1 == fin) { // vector 2 elementos
        if (v[ini] == v[fin]) return 1;
        else return 2;
    }
    if (v[ini] == v[fin]) return 1; // Para optimizar
    else { // vector de 3 o mas elementos
        int mitad = (ini + fin) / 2;
        if (v[mitad] != v[mitad-1] && v[mitad] != v[mitad + 1]){ // Elemento central diferente
            return resolver(v,ini,mitad-1) + resolver(v,mitad+1,fin) + 1;
        }
        else if (v[mitad] == v[mitad+1]) { // Se parte un intervalo al hacer las nuevas llamadas
            return resolver(v,ini,mitad) + resolver(v,mitad+1,fin)-1;
        }
        else { // Las llamadas se hacen con intervalos diferentes
            return resolver(v,ini,mitad-1) + resolver(v,mitad+1,fin);
        }
    }
}

bool resuelveCaso() {
    int numElems;
    std::cin >> numElems;
    if (numElems == 0) return false;
    std::vector<int> v(numElems);
    for (int i = 0; i < numElems; ++i) {
        std::cin >> v[i];
    }
    if (numElems != 0) {
        int n = resolver(v, 0, v.size()-1);
        std::cout << n;
    }
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