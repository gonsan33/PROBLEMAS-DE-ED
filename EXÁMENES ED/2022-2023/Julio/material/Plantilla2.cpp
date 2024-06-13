
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



    // Aqui función recursiva que resuelve el problema



void resuelveCaso() {
    // Lectura de los datos del árbol
    auto arbol = leerArbol(0);
    
    
    // LLamar a la función que resuelve el problema y escribir el resultado
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

