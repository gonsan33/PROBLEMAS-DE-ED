// ****  IMPORTANTE  ******

// Nombre y apellidos del estudiante

// Usuario del juez de examen

//*************************************


#include <iostream>
#include "bintree_eda.h"
#include <fstream>
using namespace std; 

// Explicación del algoritmo empleado




// Coste de la solución. Para justificar el coste se debe escribir la recurrencia que permite calcularlo.







// Aqui la/las función/funciones que resuelven el problema
pair<int, int> f(const bintree<int>& t, const int capacidad) {
    if (t.empty()) return { 0,0 }; 
    else {
        auto [bL, tL] = f(t.left(), capacidad); 
        auto [bR, tR] = f(t.right(), capacidad); 
        int b = bL + bR; 
        int tes; 
        if (t.root() > tL + tR) {
            b += (t.root() - (tL + tR)) / capacidad + ((t.root() - (tL + tR)) % capacidad != 0 ? 1 : 0); 
            tes = ((t.root() - (tL + tR)) % capacidad != 0 ? (capacidad - (((t.root() - (tL + tR)) % capacidad))) : 0) ;
        }
        else {
            tes = tL + tR - t.root();
        }
        return { b,tes };
    }
}



// Resuelve cada caso de entrada
void resuelveCaso() {
    // Lectura de los datos
    auto arbol = leerArbol(-1);
    int n; std::cin >> n;

    // Aqui la llamada a la función que resuelve el problema
    auto[barcos, tesoros] = f(arbol,n); 

    // Aqui escribir los resultados de la llamada a la función
    cout << barcos << " " << tesoros << '\n'; 
}



int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to sample2.txt
#endif

    int numCasos = 1;  std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
