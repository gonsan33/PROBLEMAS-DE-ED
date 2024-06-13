
// ED Junio 2023. Grupo A
// Ejercicio 2

//****************************************************
//
// IMPORTANTE
//
// Nombre y apellidos
// Usuario del juez usado en esta prueba
//
//**************************************************** 


#include <iostream>
#include <fstream>
#include <iomanip>   

#include "bintree_eda.h"
using namespace std; 


    // Aqui función recursiva que resuelve el problema
tuple<int, int> cueva(const bintree<int>& tree) { //oro máximo, vida mínima requerida 
    if (tree.empty()) return { 0,1}; 
    else {
        
        auto [oL, vL] = cueva(tree.left()); 
        auto [oR, vR] = cueva(tree.right()); 
        int o, v, ve; 
        if (oL < oR) {
            o = oR; 
            v = vR; 

        }
        else if (oL > oR) {
            o = oL; 
            v = vL; 
        }
        else {
            o = oL; 
            v = min(vL, vR); 
        }
        if (tree.root() > 1) {
            o += tree.root();
        }
        else if (tree.root() == 1 && v > 1) v -= 1;
        else if(tree.root() < 0) v -= tree.root(); 

        return { o,v }; 

    }
}


void resuelveCaso() {
    // Lectura de los datos del árbol
    auto arbol = leerArbol(0);
    
    
    // LLamar a la función que resuelve el problema y escribir el resultado
    auto [o, v] = cueva(arbol); 
    cout << o << " " << v << '\n';
}


int main() {
  
#ifndef DOMJUDGE
    std::ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
    int numCasos = 1;  std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i){ 
        resuelveCaso();
    }
    
 
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
  
    return 0;
}

