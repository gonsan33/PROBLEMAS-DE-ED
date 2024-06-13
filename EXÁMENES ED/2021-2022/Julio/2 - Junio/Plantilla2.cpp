//*****************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la solución y justificación del coste de tu algoritmo.














#include <iostream>
#include <fstream> 

#include "bintree_eda.h"
using namespace std; 

// Aqui el código del alumno
// Puedes definir las funciones auxiliares que necesites

bintree<int> acumula(const bintree<int>& arbol) {    
    if (arbol.empty()) return  bintree<int>();
    else if (arbol.left().empty() && arbol.right().empty()) return bintree<int>(bintree<int>(), arbol.root(), bintree<int>());
    else {
        bintree<int> l = acumula(arbol.left());
        bintree<int> r = acumula(arbol.right());
        return { bintree<int>(l, (l.empty() ? 0 : l.root()) + (r.empty() ? 0 : r.root()),r) };
    }
}

void resuelve() {
    // Leer los datos
   auto arbol = leerArbol(-1);
    // LLamada a la función que resuelve el problema
    auto aux = acumula(arbol);
    // Escribir los resultados
    auto sol = aux.preorder();
    if (!sol.empty()){
        std::cout << sol[0];
        for (int i = 1; i < sol.size(); ++i) 
            std::cout << ' ' << sol[i];
    }
    std::cout << '\n';
}

int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif
    
    int numCasos = 1;   std::cin >> numCasos; std::cin.ignore();    
    for (int i = 0; i < numCasos; ++i) resuelve();
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}
