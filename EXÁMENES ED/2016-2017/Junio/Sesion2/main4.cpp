// Isabel Pita. Usuario del examen: E72
// Puesto en el laboratorio P1001

#include <iostream>
#include <fstream>
#include <vector>

// Explicación: Se recorren a la vez los vectores a y b. Si el elemento a tratar en el vector a es menor que el de b, es el momento de tratar el elemento a[i], para ello, se actualiza el valor del resultado r (los elementos mayores son los que quedan desde el índice j hasta el final y los menores los que hay desde el indice j quitando los iguales al valor de a que se esta tratando). Se avanza en el vector a. Se actualiza el valor de iguales solo si el valor en el vector a cambia. En otro caso se avanza en el vector b ya que el elemento de b pasa a estar entre los menores o iguales. Se actualiza el valor de iguales dependiendo del caso.

// La función tiene coste lineal O(n + m)) siendo n el número de elementos
// del vector a y m el numero de elementos del vector b. En cada vuelta del bucle se incrementa en uno o bien el indice del vector a o bien el indice del vector b. En el peor caso se incrementan los dos índices hasta alconzar los tamaños de los vectores. El coste de cada vuelta es constante.

int  resolver(std::vector<int> const& a, std::vector<int> const& b)
{
    // aquí tu código
    //Inicializaciones
    int i = 0, j = 0;
    int r = 0, iguales = 0;
    // Bucle principal hasta que se acaba alguno de los vectores
    while (i < a.size() && j < b.size())
    {
        if (a[i] < b[j]) {
            r = r + (b.size()-j) * (j-iguales);
            if (i < a.size() - 1 && a[i+1] != a[i]) iguales = 0;
            i = i + 1;
        }
        else if (a[i] == b[j]) {
            iguales = iguales + 1; j = j + 1;
        }
        else {   // b[i] < a[i]
            iguales = 0; j = j + 1;
        }
    }
    return r;
    
}


void resuelveCaso() {
    int numElemsA, numElemsB;
    std::cin >> numElemsA;
    // Lectura de  los elementos del vector a
    std::vector<int> a(numElemsA);
    for (int i = 0; i < numElemsA; ++i)
        std::cin >> a[i];
    // Lectura de los elementos del vector b
    std::cin >> numElemsB;
    std::vector<int> b(numElemsB);
    for (int i = 0; i < numElemsB; ++i)
        std::cin >> b[i];
    // Solucion
    int suma = resolver(a,b);
    
    std::cout << suma << '\n';
}
#define DOMJUDGE

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample4-in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to sample4-in.txt
#endif
    
    
    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
    
    
    // Para restablecer entrada. Comentar para acepta el reto
    
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    
    return 0;
}
