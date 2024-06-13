//******************************************************
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
template<typename U> 
pair<int, int> caminoProp(const bintree<int>& tree, const U& func) {
    if (tree.empty()) return { 0,0 }; 
    else {
        auto [mL, rL] = caminoProp(tree.left(), func); 
        auto [mR, rR] = caminoProp(tree.right(), func); 

        int r = max(rL, rR) + (func(tree.root()) ? 1 : 0); 
        int m = max(max(mL, mR), rL+rR + (func(tree.root()) ? 1 : 0));
        return { m, r }; 
    }
}



int caminoPares (bintree<int> const& a) {

    // Codigo del alumno.
    return caminoProp(a, [](int x) {return x % 2 == 0; }).first; 

    
}

// No modificar el código a partir de aqui.
// Entrada y salida de datos
void resuelveCaso(){
    bintree<int> a = leerArbol(-1);
    std::cout << caminoPares(a) << '\n';
}

int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("casos1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif
    
    int numCasos = 1;   std::cin >> numCasos; std::cin.ignore();    
    for (int i = 0; i < numCasos; ++i) resuelveCaso();
    
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}
