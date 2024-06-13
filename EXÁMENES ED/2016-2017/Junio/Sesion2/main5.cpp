// Isabel Pita. Usuario del examen E72
// Puesto en el laboratorio 1001

#include <iostream>
#include <fstream>
#include <vector>

// Parámetros, vA vector principal, vB vector al que le falta un elemento, ini principio de ambos vectores, fin elemento siguiente al último del vector vA
// Caso base: Vector principal (vA) de un solo elemento. El elemento que falta en vB es ese elemento.
// Caso recursivo. Comparar los elementos centrales de los dos vectores. Si el de vA es menor el elemento que falta debe estar en la mitad izquierda del vector. Si los elementos son iguales el elemento que falta debe estar en la mitad derecha. No puede darse el caso de que el elemento central de vA sea mayor que el de vB ya que los vectores tienen los mismos elementos menos uno.
// Coste del algoritmo, logaritmico respecto al número de elementos del vector vA. El vector se divide por la mitad en cada llamada recursiva y se realiza una única llamada con uno de los dos lados (con la mitad de elementos)
int resolver(std::vector<int> const& vA, std::vector<int> const& vB, int ini, int fin)
{
    if (ini == fin - 1) return vA[ini]; // caso base
    else { // caso recursivo
        int mitad = (ini + fin - 1) / 2;
        if (vA[mitad] < vB[mitad]) return resolver(vA, vB, ini, mitad + 1);
        else  // tienen que ser iguales el caso vA[mitad] > vB[mitad] es imposible
            return resolver(vA,vB,mitad + 1, fin);
    }
}


void resuelveCaso() {
    int numA;
    // lectura del vector A
    std::cin >> numA;
    std::vector<int> vA(numA);
    for (int i = 0; i < numA; ++i)
        std::cin >> vA[i];
    // lectura del vector B
    std::vector<int> vB(numA-1);
    for (int j = 0; j < numA - 1; ++j)
        std::cin >> vB[j];
    // resolver
    int n = resolver(vA,vB,0,vA.size());
    // mostrar resultado
    std::cout << n << '\n';
    
}

#define DOMJUDGE

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("sample5-in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
    int casos;
    std::cin >> casos;
    for (int i = 0; i < casos; ++i)
        resuelveCaso();
    
    
    // Para restablecer entrada. Comentar para acepta el reto
    
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    
    return 0;
}
