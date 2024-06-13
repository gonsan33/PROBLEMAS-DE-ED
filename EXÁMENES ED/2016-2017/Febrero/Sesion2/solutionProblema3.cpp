// Ejercicio vuelta atras
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

enum color {AZUL, ROJO, VERDE};

std::ostream& operator<< (std::ostream& out, color c) {
    switch(c) {
        case ROJO : out << "rojo"; break;
        case VERDE : out << "verde"; break;
        case AZUL : out << "azul"; break;
    }
    return out;
}

// No pueden superarse los bloques de cada color
// No puede haber dos verdes seguidos
// En ningún momento puede haber mas verdes que azules
bool esValida(std::vector <color> const& sol, int k, int numRojos, int numVerdes, int numAzules, int altura, int a, int r, int v) {
    if (numAzules > a || numRojos > r || numVerdes > v) return false;
    if (sol[k] == VERDE && sol[k-1] == VERDE) return false;
    if (numVerdes > numAzules) return false;
    return true;
}

void escribirSolucion(std::vector <color> const& sol) {
    for (int i = 0; i < sol.size(); ++i) {
        std::cout << sol[i] << ' ';
    }
    std::cout << '\n';
}

// altura : altura de la torre a construir. No cambia de valor
// a, r, v numero inicial de bloques de cada color. No cambia su valor
// sol : solucion parcial obtenida
// k : etapa por la que vamos construyendo la solucion
// numRojos, numVerdes, numAzules : numero de bloques de cada color en la solucion parcial
// existe : cierto si se ha encontrado una solucion. Para salida final de SIN SOLUCION
void resolver (int altura, int a, int r, int v, std::vector <color> & sol, int k, int numRojos, int numVerdes, int numAzules, bool & existe) {
    for (color i = AZUL; i <= VERDE; ++i) { // En este orden para obtener la salida ordenada como se pide
        sol[k] = i;
        // marca el bloque que está utilizando
        switch (i) {
            case ROJO: ++numRojos;break;
            case VERDE: ++numVerdes;break;
            case AZUL: ++numAzules;break;
        }
        if (esValida(sol, k, numRojos, numVerdes, numAzules, altura, a, r, v)) {
            if (k == altura-1) { // es solucion
                if (numRojos > numAzules + numVerdes) { // es solucion valida
                    escribirSolucion(sol); existe = true;
                }
            }
            else { // sigue completando la solucion
                // Estimar que queden suficientes bloques rojos para cumplir las restricciones.
                if (altura - k -1 > numVerdes + numAzules -numRojos &&
                    r > numVerdes + numAzules) //Queda suficiente altura para que los rojos iguales a los verdes y azules y quedan bloques rojos para igualar a verdes y azules
                    resolver(altura, a, r, v, sol, k+1, numRojos, numVerdes, numAzules, existe);
            }
        }
        // desmarca el bloque que ha utilizado
        switch (i) {
            case ROJO: --numRojos;break;
            case VERDE: --numVerdes;break;
            case AZUL: --numAzules;break;
        }
    }
}


bool resuelveCaso() {
    int altura, a, r, v;
    std::cin >> altura;
    if (!std::cin) return false;
    std::cin >> a >> r >> v;
    std::vector<color> sol(altura);
    sol[0] = ROJO;
    if (altura == 1) std::cout << "rojo\n";
    else if (r + a + v < altura) std::cout << "SIN SOLUCION\n";
    else {
        bool existe = false;
        resolver(altura, a, r, v, sol, 1, 1, 0, 0, existe);
        if (!existe) std::cout << "SIN SOLUCION\n";
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