// ****  IMPORTANTE  ******

// Nombre y apellidos del estudiante

// Usuario del juez de examen

//*************************************


#include <iostream>
#include "bintree_eda.h"

// Explicación del algoritmo empleado




// Coste de la solución. Para justificar el coste se debe escribir la recurrencia que permite calcularlo.







// Aqui la/las función/funciones que resuelven el problema




// Resuelve cada caso de entrada
void resuelveCaso() {
    // Lectura de los datos
    auto arbol = leerArbol(-1);
    int n; std::cin >> n;
    
    // Aqui la llamada a la función que resuelve el problema
    
    
    // Aqui escribir los resultados de la llamada a la función
}



int main() {
   
#ifndef DOMJUDGE
    std::ifstream in("casos2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to sample2.txt
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
