//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la solución y justificación del coste de tu algoritmo.

/*
Uno un conjunto, para guardar los elementos que ya han aparecido. 
Como insertar y acceder a los elementos de un unordered_set tiene 
coste constante, su uso permite que el coste de la función sea lineal. 
*/

#include <iostream>
#include <fstream> 
#include <list> 
#include <unordered_set>
using namespace std; 

// Aqui el código del alumno
// Puedes definir las funciones auxiliares que necesites


template <typename T>
void eliminar_repetidos(std::list<T> & l) {

    // Codigo del alumno.
    auto it = l.begin(); 
    unordered_set<T> apariciones; 
    
    while (it != l.end()) {
        if (apariciones.count(*it)) {
            it = l.erase(it);
        }
        else {
            apariciones.insert(*it); 
            ++it;
        } 
    }
}

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso(){
    char tipo; std::cin >> tipo;
    if (!std::cin) return false;
    int numElem; std::cin >> numElem;
    if (tipo == 'N') {
        std::list<int> l;
        for (int i = 0; i < numElem; ++i) {
            int aux; std::cin >> aux; 
            l.push_back(aux);
        }
        eliminar_repetidos(l);
        for (auto n : l) std::cout << n << ' ';
        std::cout << '\n';        
    }
    else {
        std::list<std::string> l;
        for (int i = 0; i < numElem; ++i) {
            std::string aux; std::cin >> aux; 
            l.push_back(aux);
        }
        eliminar_repetidos(l);
        for (auto n : l) std::cout << n << ' ';
        std::cout << '\n';        
    }
    return true;
}

int main() {
  
#ifndef DOMJUDGE
    std::ifstream in("casos2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif  
    
    while (resuelveCaso()) ;
   
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
   
    return 0;
}
